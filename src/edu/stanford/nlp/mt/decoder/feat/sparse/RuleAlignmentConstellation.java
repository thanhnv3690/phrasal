package edu.stanford.nlp.mt.decoder.feat.sparse;

import java.util.LinkedList;
import java.util.List;

import edu.stanford.nlp.mt.decoder.feat.RuleFeaturizer;
import edu.stanford.nlp.mt.util.FeatureValue;
import edu.stanford.nlp.mt.util.Featurizable;
import edu.stanford.nlp.mt.util.IString;


/**
 * The rule alignment constellation as described by Liang et al. (2006).
 * 
 * @author Spence Green
 *
 */
public class RuleAlignmentConstellation implements
    RuleFeaturizer<IString, String> {

  public final String FEATURE_PREFIX = "ACON:";

  @Override
  public void initialize() {
  }

  @Override
  public List<FeatureValue<String>> ruleFeaturize(
      Featurizable<IString, String> f) {
    List<FeatureValue<String>> features = new LinkedList<>();
    features.add(new FeatureValue<String>(FEATURE_PREFIX
        + f.rule.abstractRule.alignment, 1.0));
    return features;
  }

  @Override
  public boolean isolationScoreOnly() {
    return false;
  }
}
