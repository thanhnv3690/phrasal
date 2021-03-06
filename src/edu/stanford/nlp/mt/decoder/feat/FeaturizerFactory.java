package edu.stanford.nlp.mt.decoder.feat;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import edu.stanford.nlp.mt.decoder.feat.base.DTULinearDistortionFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.LinearFutureCostFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.NGramLanguageModelFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.PhrasePenaltyFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.TranslationModelFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.SourceGapFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.TargetGapFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.UnknownWordFeaturizer;
import edu.stanford.nlp.mt.decoder.feat.base.WordPenaltyFeaturizer;
import edu.stanford.nlp.mt.lm.LanguageModelFactory;
import edu.stanford.nlp.mt.util.FactoryUtil;
import edu.stanford.nlp.mt.util.IString;

/**
 * Load translation model feature extractors.
 * 
 * @author danielcer
 *
 */
public final class FeaturizerFactory {

  private static final Logger logger = LogManager.getLogger(FeaturizerFactory.class.getName());
  
  public static final String MOSES_DENSE_FEATURES = "mosesdense";
  public static final String BASELINE_FEATURES = "baseline";
  public static final String DEFAULT_FEATURIZERS = MOSES_DENSE_FEATURES;
  public static final String ARPA_LM_PARAMETER = "arpalm";
  public static final String GAP_PARAMETER = "gap";
  public static final String NUM_PHRASE_FEATURES = "numphrasefeatures";

  public static final String LINEAR_DISTORTION_COST = "lineardistortion-cost";

  public enum GapType {
    none, source, target, both
  }

  private FeaturizerFactory() {} // static class

  @SuppressWarnings("unchecked")
  public static <TK, FV> Class<Featurizer<TK, FV>> loadFeaturizer(
      String name) throws ClassNotFoundException {
    return (Class<Featurizer<TK, FV>>) ClassLoader.getSystemClassLoader().loadClass(name);
  }

  /**
   * Get a feature extractor.
   * 
   * @param featurizerName
   * @param withGaps
   * @param featurizerSpecs
   * @return
   */
  public static FeatureExtractor<IString, String> factory(
      String featurizerName, boolean withGaps, String...featurizerSpecs) {
    final Map<String, String> paramPairs = FactoryUtil.getParamPairs(featurizerSpecs);
    
    // Linear distortion
    final float futureCostDelay = paramPairs.containsKey(LINEAR_DISTORTION_COST) ? 
        Float.valueOf(paramPairs.get(LINEAR_DISTORTION_COST)) : 0.0f;
    final DerivationFeaturizer<IString, String> linearDistortionFeaturizer  = 
        withGaps ? new DTULinearDistortionFeaturizer() : new LinearFutureCostFeaturizer(futureCostDelay);

    // DTU features
    List<DerivationFeaturizer<IString, String>> gapFeaturizers = new LinkedList<>();
    if (withGaps) {
      GapType gapType = GapType.valueOf(paramPairs.get(GAP_PARAMETER));
      if (gapType == GapType.source || gapType == GapType.both)
        gapFeaturizers.add(new SourceGapFeaturizer());
      if (gapType == GapType.target || gapType == GapType.both)
        gapFeaturizers.add(new TargetGapFeaturizer());
    }
    
    final int numPhraseFeatures = paramPairs.containsKey(NUM_PHRASE_FEATURES) ? 
        Integer.valueOf(paramPairs.get(NUM_PHRASE_FEATURES)) : Integer.MAX_VALUE;
    
    // Model features
    try {
      if (featurizerName.equals(BASELINE_FEATURES)) {
        if (!paramPairs.containsKey(ARPA_LM_PARAMETER)) {
          throw new RuntimeException(String.format(
              "Baseline featurizers requires that a language model is specificed using the parameter '%s'",
              ARPA_LM_PARAMETER));
        }
        List<Featurizer<IString, String>> featurizers = new LinkedList<>();
        if (withGaps) featurizers.addAll(gapFeaturizers);

        // ARPA LM
        String lm = paramPairs.get(ARPA_LM_PARAMETER);
        DerivationFeaturizer<IString, String> arpaLmFeaturizer = new NGramLanguageModelFeaturizer(
            LanguageModelFactory.load(lm));
        featurizers.add(arpaLmFeaturizer);

        // Precomputed phrase to phrase translation scores
        featurizers.add(new TranslationModelFeaturizer(numPhraseFeatures));

        // Linear distortion
        featurizers.add(linearDistortionFeaturizer);

        return new FeatureExtractor<IString, String>(featurizers);

      } else if (featurizerName.equals(MOSES_DENSE_FEATURES)) {
        List<Featurizer<IString, String>> featurizers = new LinkedList<>();
        if (withGaps) featurizers.addAll(gapFeaturizers);

        DerivationFeaturizer<IString, String> arpaLmFeaturizer;
        // ARPA LM
        String lm = paramPairs.get(ARPA_LM_PARAMETER);
        if (lm != null) {
          arpaLmFeaturizer = new NGramLanguageModelFeaturizer(
              LanguageModelFactory.load(lm));
          featurizers.add(arpaLmFeaturizer);
        }

        // Precomputed phrase to phrase translation scores
        featurizers.add(new TranslationModelFeaturizer(numPhraseFeatures));

        // Linear distortion
        featurizers.add(linearDistortionFeaturizer);

        // Word Penalty
        featurizers.add(new WordPenaltyFeaturizer<IString>());

        // Phrase Penalty
        featurizers.add(new PhrasePenaltyFeaturizer<IString>());

        // Unknown Word Featurizer
        featurizers.add(new UnknownWordFeaturizer<IString>());

        // return combined model
        return new FeatureExtractor<IString, String>(featurizers);
      } else {
        logger.error("Unrecognized feature specification: " + featurizerName);
        return null;
      }
    } catch(IOException e) {
      logger.error(e);
    }
    return null;
  }
}
