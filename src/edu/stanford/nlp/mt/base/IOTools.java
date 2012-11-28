package edu.stanford.nlp.mt.base;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Properties;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import edu.stanford.nlp.stats.Counter;
import edu.stanford.nlp.stats.Counters;
import edu.stanford.nlp.util.ErasureUtils;
import edu.stanford.nlp.util.Index;

/**
 * Various static methods for reading and writing files.
 * 
 * @author danielcer
 * @author Spence Green
 *
 */
public final class IOTools {
  
  public static List<Sequence<IString>> slurpIStringSequences(String filename)
      throws IOException {
    BufferedReader reader = new BufferedReader(new FileReader(filename));
    List<Sequence<IString>> sequences = new ArrayList<Sequence<IString>>();

    for (String inline; (inline = reader.readLine()) != null;) {
      Sequence<IString> seq = new RawSequence<IString>(
          IStrings.toIStringArray(inline.trim().split("\\s+")));
      sequences.add(seq);
    }
    reader.close();
    return sequences;
  }

  public static Set<IString> slurpIStringSet(String filename)
      throws IOException {
    Set<IString> set = new HashSet<IString>();
    if (filename == null) {
      System.err.println("IOTooks: slurpIStringSet: Warning, no file.");
      return set;
    }
    BufferedReader reader = new BufferedReader(new FileReader(filename));

    for (String inline; (inline = reader.readLine()) != null;) {
      IString w = new IString(inline.trim());
      set.add(w);
    }
    reader.close();
    return set;
  }

  public static LineNumberReader getReaderFromFile(File fileName) {
    return getReaderFromFile(fileName.getPath());
  }

  public static LineNumberReader getReaderFromFile(String fileName) {
    LineNumberReader reader; // = null;
    File f = new File(fileName);
    try {
      if (f.getAbsolutePath().endsWith(".gz")) {
        reader = new LineNumberReader(new InputStreamReader(
            new GZIPInputStream(new FileInputStream(f), 8192), "UTF-8"));
      } else {
        reader = new LineNumberReader(new InputStreamReader(
            new BufferedInputStream(new FileInputStream(f)), "UTF-8"));
      }
    } catch (IOException e) {
      e.printStackTrace();
      throw new RuntimeException("Error reading: " + fileName);
    }
    return reader;
  }

  public static PrintStream getWriterFromFile(File fileName) {
    return getWriterFromFile(fileName.getPath());
  }

  public static PrintStream getWriterFromFile(String fileName) {
    PrintStream output = null;
    try {
      if (fileName != null) {
        System.err.println("output file: " + fileName);
        if (fileName.endsWith(".gz")) {
          output = new PrintStream(new GZIPOutputStream(new FileOutputStream(
              fileName)));
        } else {
          output = new PrintStream(new FileOutputStream(fileName), false,
              "UTF-8");
        }
      }
    } catch (IOException e) {
      e.printStackTrace();
      System.exit(1);
    }
    return output;
  }

  public static void addConfigFileProperties(Properties prop, String filename)
      throws IOException {
    LineNumberReader reader = new LineNumberReader(new FileReader(filename));
    String linePattern = "(\\S+)\\s+=\\s+(\\S+)";
    Pattern pattern = Pattern.compile(linePattern);
    for (String line; (line = reader.readLine()) != null;) {
      if (line.matches("^\\s*$"))
        continue;
      if (line.charAt(0) == '#')
        continue;
      line = line.replaceAll("#.*$", "");
      Matcher matcher = pattern.matcher(line);
      if (matcher.find()) {
        assert (matcher.groupCount() == 2);
        prop.setProperty(matcher.group(0), matcher.group(1));
      }
    }
    reader.close();
  }

  /**
   * Read weights from a file. Supports both binary and text formats.
   * 
   * @param filename
   * @param featureIndex
   * @return
   * @throws IOException
   * @throws ClassNotFoundException
   */
  public static Counter<String> readWeights(String filename,
      Index<String> featureIndex) throws IOException, ClassNotFoundException {
    Counter<String> wts;
    if (filename.endsWith(".binwts")) {
      ObjectInputStream ois = new ObjectInputStream(new FileInputStream(
          filename));
      wts =  ErasureUtils.<Counter<String>>uncheckedCast(ois.readObject());
      ois.close();
    
    } else {
      wts = Counters.loadCounter(filename, String.class);
    }
    
    if (featureIndex != null) {
      for (String key : wts.keySet()) {
        featureIndex.indexOf(key, true);
      }
    }
    return wts;
  }

  /**
   * Write weights to a file. Supports both binary and text formats.
   * 
   * @param filename
   * @param wts
   */
  public static void writeWeights(String filename, Counter<String> wts) {
      try {
        if (filename.endsWith(".binwts")) {
          ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(
              filename));
          oos.writeObject(wts);
          oos.close();
        } else {
          Counters.saveCounter(wts, filename);
        }
      } catch (FileNotFoundException e) {
        e.printStackTrace();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
}
