package edu.stanford.nlp.mt.util;

import java.io.IOException;
import java.io.LineNumberReader;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Parallel corpus.
 * 
 * NOTE: The fields are public, non-final for fast serialization/deserialization.
 * 
 * @author Spence Green
 *
 */
public class ParallelCorpus implements Iterable<AlignedSentence>, Serializable {
  
  /**
   * TODO(spenceg) Replace with kryo
   */
  private static final long serialVersionUID = 5837610708369154242L;

  private static transient final Logger logger = LogManager.getLogger(ParallelCorpus.class);

  private static final int DEFAULT_CAPACITY = 10000;
  
  public List<AlignedSentence> corpus;
  public TranslationModelIndex index;
  
  /**
   * Constructor.
   */
  public ParallelCorpus() {
    this(DEFAULT_CAPACITY);
  }
  
  /**
   * Constructor.
   * 
   * @param initialCapacity
   */
  public ParallelCorpus(int initialCapacity) {
    this(DEFAULT_CAPACITY, false);
  }
  
  /**
   * Constructor.
   * 
   * @param initialCapacity
   * @param isDecoderLocal
   */
  public ParallelCorpus(int initialCapacity, boolean isDecoderLocal) {
    corpus = new ArrayList<>(initialCapacity);
    boolean isSystemIndex = ! isDecoderLocal;
    index = new TranslationModelIndex(initialCapacity, isSystemIndex);
  }

  public AlignedSentence add(String source, String target, String align) {
    int[] f = stringToArray(source);
    int[] e = stringToArray(target);
    int[][] f2e = alignStringToArray(align, f.length, e.length);
    AlignedSentence s = new AlignedSentence(f, e, f2e);
    corpus.add(s);
    return s;
  }
  
  private int[] stringToArray(String string) {
    String[] tokens = string.trim().split("\\s+");
    int[] indices = new int[tokens.length];
    for (int i = 0; i < tokens.length; ++i) {
      indices[i] = index.add(tokens[i]);
    }
    return indices;
  }
  
  @SuppressWarnings({ "unchecked", "rawtypes" })
  public static int[][] alignStringToArray(String alignStr, int sourceLen, int targetLen) {
    Set[] f2e = new HashSet[sourceLen];
    String[] alignmentPoints = alignStr.split("\\s+");
    for (String point : alignmentPoints) {
      int srcPos = Integer.parseInt(point.substring(0, 1));
      if (srcPos < 0 || srcPos >= sourceLen) {
        throw new ArrayIndexOutOfBoundsException(String.format("Source length: %d  source index: %d", sourceLen, srcPos));
      }
      if (f2e[srcPos] == null) f2e[srcPos] = new HashSet<>();
      for (String tgtStr : point.substring(2, point.length()).split(",")) {
        if (tgtStr.length() == 0)
          continue;
        int tgtPos = Integer.parseInt(tgtStr);
        if (tgtPos < 0 || tgtPos >= targetLen) {
          throw new ArrayIndexOutOfBoundsException(String.format("Target length: %d  target index: %d", targetLen, tgtPos));          
        }
        f2e[srcPos].add(tgtPos);
      }
    }

    // Convert to a grid of alignment points
    int[][] f2eArr = new int[sourceLen][];
    for (int i = 0; i < sourceLen; ++i) {
      if (f2e[i] == null) {
        f2eArr[i] = new int[0];
      } else {
        f2eArr[i] = f2e[i].stream().mapToInt(x -> (int) x).sorted().toArray();
      }
    }
    return f2eArr;
  }
  
  public AlignedSentence get(int sourceId) {
    if (sourceId < 0 || sourceId >= corpus.size()) {
      throw new ArrayIndexOutOfBoundsException();
    }
    return corpus.get(sourceId);
  }

  public int size() { return corpus.size(); }
  
  @Override
  public Iterator<AlignedSentence> iterator() {
    return corpus.iterator();
  }
  
  /**
   * Load a corpus from an aligned bitext.
   * 
   * @param sourceFile
   * @param targetFile
   * @param alignmentFile
   * @param expectedSize
   * @param isDecoderLocal 
   * @return
   * @throws IOException
   */
  public static ParallelCorpus loadCorpusFromFiles(String sourceFile, String targetFile,
      String alignmentFile, int expectedSize, boolean isDecoderLocal) throws IOException {
    boolean isSystemIndex = ! isDecoderLocal;
    ParallelCorpus corpus = new ParallelCorpus(expectedSize, isSystemIndex);
    LineNumberReader srcReader = IOTools.getReaderFromFile(sourceFile);
    LineNumberReader tgtReader = IOTools.getReaderFromFile(targetFile);
    LineNumberReader algnReader = IOTools.getReaderFromFile(alignmentFile);
    for (String srcLine; (srcLine = srcReader.readLine()) != null;) {
      String tgtLine = tgtReader.readLine();
      String algnLine = algnReader.readLine();
      corpus.add(srcLine, tgtLine, algnLine);
    }
    srcReader.close();
    tgtReader.close();
    algnReader.close();
    return corpus;
  }
}