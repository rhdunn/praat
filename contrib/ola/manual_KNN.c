/* manual_KNN.c
 *
 * Copyright (C) 2007-2008 Ola Söder
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* $URL: svn://pegasos.dyndns.biz/praat/trunk/kNN/manual_KNN.c $
 * $Rev: 137 $
 * $Author: stix $
 * $Date: 2008-08-10 19:34:07 +0200 (Sun, 10 Aug 2008) $
 * $Id: manual_KNN.c 137 2008-08-10 17:34:07Z stix $
 */

/*
 * os 20080529 Initial release
 */

#include "ManPagesM.h"
#include "KNN.h"

void manual_KNN_init (ManPages me);

void manual_KNN_init (ManPages me)
{
    MAN_BEGIN (L"kNN classifiers", L"Ola S\\o\"der", 20080529)
    INTRO (L"This tutorial describes the use of kNN classifiers in P\\s{RAAT}. ")
    NORMAL (L"@@kNN classifiers 1. What is a kNN classifier?|1. What is a kNN classifier?@")
    NORMAL (L"@@kNN classifiers 1.1. Improving classification accuracy|1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting|1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.1. Filter-based feature weighting|1.1.1.1. Filter-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.2. Wrapper-based feature weighting|1.1.1.2. Wrapper-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.2. Model selection|1.1.2. Model selection@")
    NORMAL (L"@@kNN classifiers 1.2. Improving resource efficiency|1.2. Improving resource efficiency@")
    LIST_ITEM (L"@@kNN classifiers 1.2.1. Pruning|1.2.1. Pruning@")
    NORMAL (L"@@kNN classifiers 2. Quick start|2. Quick start@")
    NORMAL (L"@@kNN classifiers 3. Command overview|3. Command overview@")
    MAN_END

    MAN_BEGIN (L"KNN", L"Ola S\\o\"der", 20080529)
    INTRO (L"One of the @@types of objects@ in P\\s{RAAT}.")
    NORMAL (L"A #KNN classifier can %learn associations between its %input and its %output. "
            "The @@kNN classifiers@ tutorial gives you an introduction to the usage of %%k%NN learners in P\\s{RAAT}.")
    MAN_END

    MAN_BEGIN (L"FeatureWeights", L"Ola S\\o\"der", 20080729)
    INTRO (L"One of the @@types of objects@ in P\\s{RAAT}.")
    NORMAL (L"A @FeatureWeights object is a %d-dimensional vector containing weight values used to transform a %d-dimensional space. Feature weighting can be used to improve the classifcation accuracy of @KNN classifiers. It can also be used to generate a @Dissimilarity matrix from a @Pattern object. @Dissimilarity matrices in conjunction with @@Multidimensional scaling|MDS-analysis@ can aid the visualization of high-dimensional data.")
    MAN_END


    MAN_BEGIN (L"kNN classifiers 1. What is a kNN classifier?", L"Ola S\\o\"der", 20080529)
    NORMAL (L"%%Instance-based% classifiers such as the %%k%NN classifier operate on the premises that classification of unknown instances can be done by relating the unknown to the known according to some @@Euclidean distance|distance/similarity function@. The intuition is that two instances far apart in the %%instance space% defined by the appropriate %%distance function% are less likely than two closely situated instances to belong to the same class.")

    ENTRY (L"The learning process")

    NORMAL (L"Unlike many artificial learners, %%instance-based% learners do not abstract any information from the training data during the learning phase. Learning is merely a question of encapsulating the training data. The process of %generalization is postponed until it is absolutely unavoidable, that is, at the time of %classification. This property has lead to the referring to %%instance-based% learners as %lazy learners, whereas classifiers such as @@Feedforward neural networks 1. What is a feedforward neural network?|feedforward neural networks@, where proper %abstraction is done during the learning phase, often are entitled %eager learners.")

    ENTRY (L"Classification")

    NORMAL (L"Classification (%generalization) using an %%instance-based% classifier can be a simple matter of locating the nearest neighbor in %%instance space% and labeling the unknown instance with the same class label as that of the located (known) neighbor. This approach is often referred to as a %%nearest neighbor classifier%. The downside of this simple approach is the lack of robustness that characterize the resulting classifiers. The high degree of local sensitivity makes %%nearest neighbor classifiers% highly susceptible to noise in the training data.")
    NORMAL (L"More robust models can be achieved by locating %k, where %k > 1, neighbors and letting the majority vote decide the outcome of the class labeling. A higher value of %k results in a smoother, less locally sensitive, function. The %%nearest neighbor classifier% can be regarded as a special case of the more general %%k-nearest neighbors classifier%, hereafter referred to as a %%k%NN classifier. The drawback of increasing the value of %k is of course that as %k approaches %n, where %n is the size of the %%instance base%, the performance of the classifier will approach that of the most straightforward %%statistical baseline%, the assumption that all unknown instances belong to the class most most frequently represented in the training data.")
    NORMAL (L"This problem can be avoided by limiting the influence of distant instances. One way of doing so is to assign a weight to each vote, where the weight is a function of the distance between the unknown and the known instance. By letting each weight be defined by the inversed squared distance between the known and unknown instances votes cast by distant instances will have very little influence on the decision process compared to instances in the near neighborhood. %%Distance weighted voting% usually serves as a good middle ground as far as local sensitivity is concerned.")
    MAN_END


    MAN_BEGIN (L"kNN classifiers 1.1. Improving classification accuracy", L"Ola S\\o\"der", 20080529)
    NORMAL (L"This tutorial describes possible ways of improving the classification accuracy of a %%k%NN classifier.")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting|1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.2. Model selection|1.1.2. Model selection@")
    MAN_END

    MAN_BEGIN (L"kNN classifiers 1.1.1. Feature weighting", L"Ola S\\o\"der", 20080529)
    NORMAL (L"A %%k%NN classifier in its most basic form operates under the implicit assumption that all features are of equal value as far as the classification problem at hand is concerned. When irrelevant and noisy features influence the neighborhood search to the same degree as highly relevant features, the accuracy of the model is likely to deteriorate. %%Feature weighting% is a technique used to approximate the optimal degree of influence of individual features using a training set. When successfully applied relevant features are attributed a high weight value, whereas irrelevant features are given a weight value close to zero. %%Feature weighting% can be used not only to improve classification accuracy but also to discard features with weights below a certain threshold value and thereby increase the resource efficiency of the classifier.")
    NORMAL (L"Two fundamentally different approaches to this optimization problem can be identified, the %%filter-based% and the %%wrapper-based%. The class of %%filter-based% methods contains algorithms that use no input other than the training data itself to calculate the %%feature weights%, whereas %%wrapper-based% algorithms use feedback from a classifier to guide the search. %%Wrapper-based% algorithms are inherently more powerful than their filter-based counterpart as they implicitly take the %%inductive bias% of the classifier into account. This power comes at a price however; the usage of %%wrapper-based% algorithms increases the risk of %%overfitting% the training data.")
    NORMAL (L"In @@kNN classifiers 1.1.1.1. Filter-based feature weighting|section 1.1.1.1.@ the %%filter-based% feature weighting algorithm implemented in P\\s{RAAT} is presented. @@kNN classifiers 1.1.1.2. Wrapper-based feature weighting|Section 1.1.1.2.@ contains an account of the implemented %%wrapper-based% feature weighting algorithm.")
    MAN_END

    MAN_BEGIN (L"kNN classifiers 1.1.1.1. Filter-based feature weighting", L"Ola S\\o\"der", 20080529)
    NORMAL (L"The %%filter-based% %%feature weighting% algorithm implemented in P\\s{RAAT} is an extended version of the well known R\\s{ELIEF} algorithm, R\\s{ELIEF-F}, such as it is presented (with one minor exception, see below) in @@Igor Kononenko (1994)|Kononenko (1994)@. Unlike the original R\\s{ELIEF} algorithm, the R\\s{ELIEF-F} algorithm copes with multi class (as in more than 2 classes) data sets. The simple intuition behind the R\\s{ELIEF-F} algorithm is that a good feature is a feature with little within class variance and generous amounts of between-class variance. A bad feature is characterized by within-class and between-class variances of magnitudes roughly equal.")
    NORMAL (L"The computation of the weight vector is done in an iterative fashion, with all weights initially set to 0. All features in the training set are normalized (all values are set within the range [0 ... 1]) and thereafter used to update the weight vector as follows: On each iteration a random instance is chosen. The nearest hit is located, where hit is an instance of the same class as that of the randomly chosen instance. The nearest misses of all the classes but that of the randomly chosen instance are located, where a miss is an instance of a class different from that of the randomly chosen instance. Each weight is updated by subtracting the difference between the given attribute of the randomly chosen instance and that of the nearest hit and adding the corresponding difference between the chosen instance and all the nearest misses weighted by the prior probabilities of their classes. If the distance between the attribute of the randomly chosen instance and the nearest hit equals the corresponding value for the nearest miss(es) then the weight value will not change, it will thus remain 0 given that the current iteration is the first one. If the difference between the attribute of the chosen instance and the nearest hit is lower than the corresponding value for the miss(es) then the weight value will be increased. On average highly significant attributes will result in absolute values distinct from 0, leading to an absolute increase of the weight, and insignificant attributes will on average result in values near 0, retaining the pessimistic view that all features are of no value as predictors.")
    NORMAL (L"The implementation of R\\s{ELIEF-F} found in P\\s{RAAT} differs slightly from the algorithm described. Instances are not randomly chosen, instead all instances are used to update the weight vector. This simplification is of no concern unless massive data sets are used, in which case the P\\s{RAAT} approach would be no less precise, but needlessly slow.")
    MAN_END

    MAN_BEGIN (L"kNN classifiers 1.1.1.2. Wrapper-based feature weighting", L"Ola S\\o\"der", 20080529)
    NORMAL (L"The %%wrapper-based% %%feature weighting% algorithm implemented in P\\s{RAAT} attempts to find the globally optimal feature weights by means of a greedy local search. The local neighborhood is defined by a number of random seeds centered around a pivot seed. For each iteration of the algorithm the best performing seed is chosen to be the pivot of the next iteration. At the same time the maximum allowed distance between a seed and the pivot is decreased by a constant factor. Given a sufficient number of seeds and a small shrinkage factor the algorithm will on average home in on a good approximation of the global maximum.")
    NORMAL (L"The method can be regarded as a simplification of the proven %%simulated annealing% algorithm. The most important difference between the implemented search algorithm and %%simulated annealing% is that simulated annealing tolerates performance degradations (translated into the current terminology, %%simulated annealing% does not always pick the best seed for its next pivot, with low probability a less fit seed is chosen) whereas the currently implemented algorithm always opts for a better performing seed and if no such seed exists retains the current pivot seed. This makes the algorithm simpler, but at the same time more susceptible to getting stuck in local maxima.")
    NORMAL (L"Given reasonable parameter settings, the search algorithm on average gives good results without huge memory and CPU requirements. The strong point of the method, the ability to efficiently do a rather thorough search of the weight space, can, as mentioned in @@kNN classifiers 1.1.1. Feature weighting|section 1.1.1.@, lead to overfitting. One way of minimizing this problem is to constrain the algorithm by means of %%early stopping%. In P\\s{RAAT} this is done in a very naive fashion, by simply not allowing the algorithm to explore weights achieving an accuracy higher than a specified threshold value.")
    MAN_END


    MAN_BEGIN (L"kNN classifiers 1.1.2. Model selection", L"Ola S\\o\"der", 20080529)
    NORMAL (L"%%Model selection% is the process of choosing classifier parameters suitable for the classification task at hand. In most cases this is done manually in an experimental fashion.")
    NORMAL (L"The search for the optimal model can also be automated. In P\\s{RAAT} this is done by means of the same @@kNN classifiers 1.1.1.2. Wrapper-based feature weighting|greedy local search algorithm@ used to search the weight space for feature weights. The %%model selection% search implementation in P\\s{RAAT} lets the user limit the search space with respect to the parameter %k. By setting a maximum allowed value of %k the search space can be shrunk considerably.")
    NORMAL (L"Due to its discrete (%k) and nominal (vote weighting) nature, the size of the search space is normally of no concern, making an experimental/manual search tractable. The %%model selection% feature of P\\s{RAAT} becomes an essential tool only when applied to huge instance bases where the expected optimal value of %k is high. In most cases however, manual experimenting will suffice.")
    MAN_END

    MAN_BEGIN (L"kNN classifiers 1.2. Improving resource efficiency", L"Ola S\\o\"der", 20080529)
    NORMAL (L"%%Instance-based% learners such as the %%k%NN classifier implemented in P\\s{RAAT} are fairly inefficient as far as CPU and memory usage is concerned. The efficiency of %%instance-based% learners can be fundamentally improved upon by storing the instances in such a way that the %k nearest neighbors can be located without doing an exhaustive search of the instance space. By storing instances in tree structures the search of the instance space can be done in logarithmic time compared to the linear time complexity of the naive list approach. Similar gains in performance can be achieved by making sure that only those instances that are vital for the accuracy of the classifier are stored and that non-vital instances are disposed of. The current implementation in P\\s{RAAT} makes no use of tree structures, it does however give the user the possibility to prune non-vital or harmful instances, making the resulting classifier less memory and CPU hungry and in some cases more accurate even though that is not the primary objective of the pruning algorithm.")
    MAN_END

    MAN_BEGIN (L"kNN classifiers 1.2.1. Pruning", L"Ola S\\o\"der", 20080529)
    NORMAL (L"Pruning is the process of discarding instances that do not improve upon the classification accuracy of the classifier. This group of instances includes noisy instances that, at best, make no difference as far as model accuracy is concerned, at worst, induces classification errors. It also includes instances that are redundant; instances that are implied by the defined neighborhood.")

    ENTRY (L"The C-Pruner algorithm")

    NORMAL (L"The C-Pruner algorithm such as it is presented in @@Ke-Ping Zhao et al. (2003)|Zhao et al. (2003)@ identifies pruning candidates and computes the order in which these candidates shall be removed. The ordering is of vital importance since the removal of one candidate might disqualify other candidates, making them non-prunable. In order to understand how the C-Pruner algorithm operates a few definitions are necessary:")

    LIST_ITEM (L"\\bu The %k-reachability set of an instance %p consists of the %k nearest neighbors of %p")

    LIST_ITEM (L"\\bu The %k-coverage set of an instance %p consists of those instances of the same class as that of %p having %p as one of their %k nearest neighbors.")

    LIST_ITEM (L"\\bu An instance %p is superfluous if it is implied by %k-reachability, that is, if it can be correctly classified using %k-reachability as instance base.")

    LIST_ITEM (L"\\bu An instance %p is critical if at least one instance in the %k-coverage set of %p is not implied by the %k-reachability set of %p or, after %p is deleted, atleast one instance in the %k-coverage set of %p is not implied by the %k-reachability set of %p.")

    LIST_ITEM (L"\\bu An instance %p is noisy if %p isn't superfluous and the %k-reachability set of %p is bigger than the %k-coverage set of %p.")

    NORMAL (L"Given these definitions, an instance is tagged for pruning if one of the following conditions hold: It is noisy, or it is superfluous but not critical. This translates to the discarding of instances that are bad class predictors (noise) and of instances that are highly typical of their class and thus are located close to the center of the cluster defining the given class. Instances located close to the class center are very likely implied by the surrounding border instances and thus redundant. In order to avoid destructive domino effects it is important that the pruning starts close to the center of the cluster and works its way out and not the other way around. To impose this ordering the C-Pruner algorithm uses the following heuristics to determine the order of removal of two superfluous instances %p__i_ and %p__j_:")

    LIST_ITEM (L"\\bu If the %k-reachability set of %p__i_ contains more instances of the same class as that of %p__i_ than the corresponding value for %p__j_ then %p__i_ should be removed before %p__j_.")

    LIST_ITEM (L"\\bu If the %k-reachability set of %p__i_ contains the same number of instances of the same class as that of %p__i_ as the corresponding value for %p__j_ and the distance between %p__i_ and the closest instance of a class different from the class of %p__i_ is greater than the corresponding value for %p__j_ then %p__i_ should be removed before %p__j_.")

    LIST_ITEM (L"\\bu If the %k-reachability set of %p__i_ contains the same number of instances of the same class as that of %p__i_ as the corresponding value for %p__j_ and the distance between %p__i_ and the closest instance of a class different from the class of %p__i_ equals the corresponding value for %p__j_ then the order of removal is decided randomly.")

    NORMAL (L"In order to gain control of the degree of pruning the P\\s{RAAT} implementation of the C-Pruner algorithm decides whether to prune or not prune a given instance tagged for pruning on a probabilistic basis. This makes it possible for the user to specify the hardness of the pruning process (e.g. 100 percent (exp.) noise, 50 percent (exp.) redundancy) to be able to find a good compromise between model accuracy and resource requirements.")
    MAN_END

    MAN_BEGIN (L"kNN classifiers 2. Quick start", L"Ola S\\o\"der", 20080809)
/*
    ENTRY (L"Creating a kNN classifier")
    NORMAL (L"A %%k%NN classifier can be created by selecting #New \\=> ##kNN classifiers# \\=> ##Create kNN classifier# in the ##Praat objects# window. A form prompting for a name of the classifier to be created will be shown.")

    NORMAL (L"An alternative way of creating a %%k%NN classifier is to select a @Pattern object and a @Categories object and choose ##To kNN classifier...#. The number of rows in the @Pattern object must match the number of categories in the @Categories object otherwise the creation of the classifier will fail.")

    NORMAL (L"Besides prompting for a name the shown form lets the user specify the ordering of the instances in the instance base to be created. If ##random# is selected the input instances will be stored in random order, if ##sequential# is chosen the instance base will retain the order set by the input data. If the input data is sorted by category, sequential learning can lead to misleading accuracy estimates if accuracy is estimated by means of 10-fold cross validation. By choosing ##random# this is avoided. If the training data is already shuffled or if the learning phase is time critical (sequential learning is faster) ##sequential# might be the better choice.")


    ENTRY (L"Training")
    NORMAL (L"Unless the classifier is created by the selection of a @Pattern object and a @Categories object and choosing ##To kNN classifier...# the classifier must be feed with training data in order to function. This is done by selecting the #KNN object, a @Pattern object and a @Categories object and then selecting ##Learn...#. The form mentioned above (see Creating a %%k%NN classifier) will prompt for a name and the ordering in which the instances will be inserted in the instance base. ")
    NORMAL (L"If the above is done using an already trained %%k%NN classifier then the option of replacing the current instance base or appending the training data to the current instance base will be given. This will only succeed if the number of features in the old instance base and the number of features in the training data match.")


    ENTRY (L"Classification")
    NORMAL (L"A #KNN object can be used for classification by selecting the classifier object and a @Pattern object and choosing either ##To Categories...# or ##To TableOfReal...#. By choosing ##To Categories...# and setting the appropriate classifier parameters (a form prompting for the value of %k and the type of vote weighting to be used will be shown) a @Categories object containing the class labels of the input data will be created. If ##To TableOfReal...# is chosen then a @TableOfReal object containing verbose information on the process of decision will be generated. Apart from the winning class label, the @TableOfReal object contains information on the number same-class instances within the neighborhood (defined by %k) and the average distance to these. It also contains information representing the probability that the current classification is correct. Two probability values are given, one where the within-neighborhood distances are taken into account, given that vote weighting is used, and one where all instances within the neighborhood are considered equally significant. The form shown upon choosing ##To TableOfReal...# will, on top of the standard classifier parameters, prompt for a value of the binary parameter labeled #Output. If ##Winners only# is set then only information regarding the winning category will be written to the @TableOfReal object. If ##All candidates# are chosen then information regarding all instances in the neighborhood will be written to the @TableOfReal object, where classification of a single input instance can be identified by the summing of the probability values of the output categories.")



    ENTRY (L"Evaluation")
    NORMAL (L"The accuracy of a classifier can be estimated by selecting the classifier object and ##Query - # \\=> ##Get accuracy estimate...#. A form prompting for model parameters and estimation method (%%10-fold cross validation% / %%leave-one-out%) will be shown. If the classifier is selected together with an @FeatureWeights object then the estimate will be made using the feature weights contained within the @FeatureWeights object.")
    NORMAL (L"The accuracy estimate can also be computed using a separate test set. In order to do so select the classifier, a @Pattern object and a @Categories object and choose ##Evaluate...#. The form shown will equal the one described above except for the absence of the estimation method options. If an @FeatureWeights object is selected together with the classifier and the test set the contained feature weights will be used.")

    ENTRY (L"Feature weighting")
    NORMAL (L"The approximation of feature weights can be done by selecting a %%k%NN classifier object and choosing ##To FeatureWeights...#. The form shown will prompt for quite a few parameters, where the most significant ones are ##Learning rate.#, ##Number of seeds# and ##Stop at#.")
    NORMAL (L"The learning rate specifies how quickly the algorithm will home in on the final result, a lower value will generally, at the price of longer processing times, result in a better approximation of the global maximum. Valid values of the learning rate are 0 (exclusive) ... 1 (inclusive), where values near 1 make little sense.")
    NORMAL (L"The number of seeds specifies the size of the neighborhood used in the local search. A bigger neighborhood generally results in a more reliable outcome. The drawback of a high number of seeds is increased processing times.")
    NORMAL (L"The ##Stop at# parameter constitutes a bound on the model accuracy estimate done by means of either %%10-fold cross validation% or %%leave-one-out%. A value of 1 imposes no restrictions on the approximated accuracy, whereas as value of 0.5 will result in the algorithm stopping if weights resulting in an approximated accuracy equal to, or above, 50 percent are found. ")
    NORMAL (L"The #Optimization option lets the user specify whether the algorithm shall search for one feature weight at a time or do a complete search for all feature weights simultaneously.")
    NORMAL (L"The remaining parameters control the evaluation of the found weights. Apart from the evaluation method options (%%10-fold cross validation% and %%leave-one-out%) the customary %%k%NN model parameters can be specified.")
*/

    ENTRY (L"An example: Learning the Iris data set")
    NORMAL (L"In the @@Feedforward neural networks|the feedforward neural networks tutorial@ a description of how the @FFNet classifier in P\\s{RAAT} can be applied to @@iris data set|the Iris data set@ can be found.")
    NORMAL (L"The same data can be used to test the %%k%NN feature of P\\s{RAAT}. To do so create an example data set using the @@Create iris example...@ command found in the ##Neural nets# submenu. The form prompting for network topology settings can be ignored by selecting OK. Select the newly created @Pattern and @Categories objects and click ##To KNN Classifier...#. A form prompting for a name of the classifier to be created will be shown. The ordering in which instances are to be inserted into the instance base can also be specified, make sure that #Random is selected and thereafter close the form by selecting OK. The newly created and trained classifier will be shown in the list of objects.")
    NORMAL (L"To estimate how well the classifier can be expected to classify new samples of Irises select ##Query -# \\=> ##Get accuracy estimate...#. A form prompting for %%k%NN parameter settings and evaluation method will be shown. Experiment with the parameter settings until satisfactory results are achieved. If everything worked out the estimate will likely end up somewhere in the range of 94-98 percent.")
    NORMAL (L"An alternative to manually experimenting with model parameters is to let the computer do the job. This is done be choosing the @KNN object and thereafter selecting ##Query -# \\=> ##Get optimized parameters...#. The form shown prompts for a selection of parameters controlling the search. The default values will in most cases, including this, be appropriate.")
    NORMAL (L"Another way of improving classification accuracy is to transform the instance space in which the individual instances, in this case Irises, are stored as to maximize the distance between instances of different classes and minimize the distance between instances of the same class. This can be done by means of feature weighting. To do so select the @KNN object and choose ##To FeatureWeights...#. Adjust the %%k%NN settings according to the ones found by the model search algorithm and let the remaining options retain the default values. Click OK. A @FeatureWeights object will be added to the objects list. The feature weights contained within the newly created object can be used by selecting named object in conjunction with the @KNN classifier and thereafter choosing the desired action.")

/*
    ENTRY (L"Pruning")
    NORMAL (L"The instance base of a %%k%NN classifier can be pruned by selecting the classifier object and choosing ##Modify -# \\=> ##Prune...#. A form prompting for the degree of pruning (noise and redundancy) and a value of the parameter %k will be shown. A pruning degree of 1 means that the algorithm will, with 100 percent certainty, prune an instance tagged for pruning. A pruning degree of 0.5 will %%on average% result in the retaining of 50 percent of the instances tagged as prunable. The value of %k is normally chosen to equal the value selected for classification.")

    ENTRY (L"Miscellaneous")
    NORMAL (L"The features listed below are normally of little value when P\\s{RAAT} is used in interactive mode. Their intended primary use is as utility functions in P\\s{RAAT} scripts.")
    LIST_ITEM (L"\\bu The size of the instance base of a classifier can be probed by selecting the classifier object and choosing ##Query -# \\=> ##Get size of instance base#. ")
    LIST_ITEM (L"\\bu The instance base of a classifier can be shuffled by selecting the classifier object and choosing ##Modify -# \\=> #Shuffle.")
    LIST_ITEM (L"\\bu All instances in the instance base of a classifier can be deleted by selecting the classifier object and choosing ##Modify -# \\=> ##Reset...#.")
    LIST_ITEM (L"\\bu The @Pattern object containing the vectors representing the instances of a classifier can be extracted by selecting the classifier object and choosing ##Extract -# \\=> ##Extract input Patterns#.")
    LIST_ITEM (L"\\bu The @Categories object representing the classes of the individual instances in the instance base can be extracted by selecting the classifier object and choosing ##Extract -# \\=> ##Extract output Categories#.")

*/
    MAN_END



    MAN_BEGIN (L"k-means clustering", L"Ola S\\o\"der", 20080529)
    INTRO (L"This tutorial describes the use of %%k%-means clustering in P\\s{RAAT}. ")
    NORMAL (L"@@k-means clustering 1. How does k-means clustering work?|1. How does k-means clustering work?@")
    NORMAL (L"@@k-means clustering 2. Quick start|2. Quick start@")
    MAN_END

    MAN_BEGIN (L"k-means clustering 1. How does k-means clustering work?", L"Ola S\\o\"der", 20080529)
    NORMAL (L"The %%k%-means clustering algorithm attempts to split a given anonymous data set (a set containing no information as to class identity) into a fixed number (%k) of clusters.")
    NORMAL (L"Initially %k number of so called %centroids are chosen. A %centroid is a data point (imaginary or real) at the center of a cluster. In P\\s{RAAT} each centroid is an existing data point in the given input data set, picked at random, such that all %centroids are unique (that is, for all %centroids %c__%i_ and %c__%j_, %c__%i_ \\=/ %c__%j_). These %centroids are used to train a @@kNN classifiers 1. What is a kNN classifier?|kNN classifier@. The resulting classifier is used to classify (using %k = 1) the data and thereby produce an initial randomized set of clusters. Each %centroid is thereafter set to the arithmetic mean of the cluster it defines. The process of classification and %centroid adjustment is repeated until the values of the %centroids stabilize. The final %centroids will be used to produce the final classification/clustering of the input data, effectively turning the set of initially anonymous data points into a set of data points, each with a class identity.")
    MAN_END

    MAN_BEGIN (L"k-means clustering 2. Quick start", L"Ola S\\o\"der", 20080529)
    NORMAL (L"Clustering using the %%k%-means clustering algorithm in P\\s{RAAT} is done by selecting a @Pattern and choosing ##To Categories...#. In the appearing requester the number of sought after clusters (unique categories) can be specified. The cluster size ratio constraint (%z) imposes a constraint on the output such that %cluster size(%x) / %cluster size(%y) > %z for all clusters %x and %y in the resulting set of clusters. Valid values of %z are 0 < %z <= 1 where values near 0 imposes practically no constraints on the cluster sizes and a value of 1 tells the algorithm to attempt to create clusters of equal size. The size ratio constraint is enforced in a very naive fashion, by random reseeding. Since this can be a rather time consuming process it is possible to set an upper bound on the number of reseeds done by the algorithm. This upper bound is defined by the parameter ##Maximum number of reseeds#. It should be noted however that normally there's no need to use the size ratio constraint, selecting the desired number of clusters will, on average, result in clusters of roughly equal size, given well distributed data.")
    MAN_END







    MAN_BEGIN (L"Pattern to Dissimilarity", L"Ola S\\o\"der", 20080529)
    NORMAL (L"A @Dissimilarity matrix can be used in conjunction with @@Multidimensional scaling|Multidimensional scaling@ to aid visualization of high-dimensional data. A @Dissimilarity object is a matrix of the distances, according to the chosen @@Euclidean distance|distance function@, between all the data points in the @Pattern object.")
    NORMAL (L"A @Dissimilarity object can be created by selecting a @Pattern object and choosing ##To Dissimilarity#. The dissimilarity matrix can also be computed using feature weights. This is done by selecting a @Pattern object, an @FeatureWeights object and choosing ##To Dissimilarity#.")
    MAN_END



    MAN_BEGIN (L"Euclidean distance", L"Ola S\\o\"der", 20080529)
    NORMAL (L"The Euclidean distance between the %n-dimensional vectors %a and %b can be calculated as follows:")

    FORMULA (L"\\De__Euclidean_(%x,%y) ="
             "\\Vr(\\su__%i=1..%n_(%a__%i_ - %b__%I_)^2)")
    MAN_END

    MAN_BEGIN (L"kNN classifiers 3. Command overview", L"Ola S\\o\"der", 20080809 )
    INTRO (L"KNN commands")
    ENTRY (L"Creation:")
    LIST_ITEM (L"\\bu @@Pattern & Categories: To KNN classifier...@")
    LIST_ITEM (L"\\bu @@Create KNN...@")
    ENTRY (L"Learning:")
    LIST_ITEM (L"\\bu @@KNN & Pattern & Categories: Learn...@")
    ENTRY (L"Classification:")
    LIST_ITEM (L"\\bu @@KNN & Pattern: To Categories...@")
    LIST_ITEM (L"\\bu @@KNN & Pattern: To TabelOfReal...@")
    LIST_ITEM (L"\\bu @@KNN & Pattern & FeatureWeights: To Categories...@")
    LIST_ITEM (L"\\bu @@KNN & Pattern & FeatureWeights: To TableOfReal...@")
    ENTRY (L"Evaluation:")
    LIST_ITEM (L"\\bu @@KNN & Pattern & Categories: Evaluate...@")
    LIST_ITEM (L"\\bu @@KNN & Pattern & Categories & FeatureWeights: Evaluate...@")
    ENTRY (L"Queries")
    LIST_ITEM (L"\\bu @@KNN: Get optimized parameters...@")
    LIST_ITEM (L"\\bu @@KNN: Get accuracy estimate...@")
    LIST_ITEM (L"\\bu @@KNN & FeatureWeights: Get accuracy estimate...@")
    LIST_ITEM (L"\\bu @@KNN: Get size of instance base@")
    ENTRY (L"Extractions")
    LIST_ITEM (L"\\bu @@KNN: Extract input Pattern@")
    LIST_ITEM (L"\\bu @@KNN: Extract output Categories@")
    ENTRY (L"Modification:")
    LIST_ITEM (L"\\bu @@KNN: Shuffle@")
    LIST_ITEM (L"\\bu @@KNN: Prune...@")
    LIST_ITEM (L"\\bu @@KNN: Reset...@")
    ENTRY (L"Miscellaneous:")
    LIST_ITEM (L"\\bu @@KNN: To FeatureWeights...@")
    LIST_ITEM (L"\\bu @@KNN & Pattern & Categories: To FeatureWeights...@") 
    LIST_ITEM (L"\\bu @@Pattern & Categories: To FeatureWeights...@")
    ENTRY (L"Pre/post processing:")
    LIST_ITEM (L"\\bu @@Pattern: To Categories...@")
    LIST_ITEM (L"\\bu @@Pattern & FeatureWeights: To Categories...@")
    LIST_ITEM (L"\\bu @@Pattern: To Dissimilarity...@")
    LIST_ITEM (L"\\bu @@Pattern & FeatureWeights: To Dissimilarity...@")
    MAN_END

    MAN_BEGIN (L"Pattern & Categories: To KNN classifier...", L"Ola S\\o\"der", 20080726 )
    INTRO (L"Create and train a @KNN classifier using the selected @Pattern and @Categories objects as training data.")
    ENTRY (L"Arguments")
    TAG (L"%%Name%")\
    DEFINITION (L"The name of the @KNN classifier.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    MAN_END

    MAN_BEGIN (L"Create KNN...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Create a new @KNN classifier.")
    ENTRY (L"Arguments")
    TAG (L"%%Name%")
    DEFINITION (L"The name of the classifier.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN & Pattern & Categories: Learn...", L"Ola S\\o\"der", 20080726 )
    INTRO (L"Train the selected @KNN classifier using the chosen @Pattern and @Categories objects as training data.")
    ENTRY (L"Arguments")
    TAG (L"%%Name%")
    DEFINITION (L"The name of the classifier.")
    TAG (L"%%Ordering%")
    DEFINITION (L"The order in which the training instances are to be inserted into the instance base.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    MAN_END

    MAN_BEGIN (L"KNN & Pattern: To Categories...", L"Ola S\\o\"der", 20080726 )
    INTRO (L"Use the selected @KNN classifier to classify the chosen @Pattern. A @Categories object containing the result will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    MAN_END

    MAN_BEGIN (L"KNN & Pattern: To TabelOfReal...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Use the selected @KNN classifier to classify the chosen @Pattern. A @TableOfReal object containing verbose information on the decision process  will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    TAG (L"%%Output%")
    DEFINITION (L"Specifies the degree of verbosity, where %%winners only% generates a @TableOfReal containing information on the instances of the winning category only whereas %%All candidates% results in a @TableOfReal with verbose information on all unique categories in the neighborhood defined by the parameter %k.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    MAN_END

    MAN_BEGIN (L"KNN & Pattern & FeatureWeights: To Categories...", L"Ola S\\o\"der", 20080726 )
    INTRO (L"Use the selected @KNN classifier and @FeatureWeights object to classify the chosen @Pattern. A @Categories object containing the result will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.1. Filter-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.2. Wrapper-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN & Pattern & FeatureWeights: To TableOfReal...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Use the selected @KNN classifier and the feature weights, @FeatureWeights, to classify the chosen @Pattern. A @TableOfReal object containing verbose information on the decision process will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    TAG (L"%%Output%")
    DEFINITION (L"Specifies the degree of verbosity, where %%winners only% generates a @TableOfReal containing information on the instances of the winning category only whereas %%All candidates% results in a @TableOfReal with verbose information on all unique categories in the neighborhood defined by the parameter %k.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.1. Filter-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.2. Wrapper-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Get optimized parameters...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Perform an automated search for the optimal @KNN parameter settings.")
    ENTRY (L"Arguments")
    TAG (L"%%Evaluation method%")
    DEFINITION (L"The method to be used for estimating the classification accuracy, which in turn is used to guide the model search. Supported methods are 10-fold cross-validation and leave-one-out.")
    TAG (L"%%k max%")
    DEFINITION (L"The maximum value of the parameter %k.")
    TAG (L"%%Number of seeds%")
    DEFINITION (L"The size of the parameter neighborhood to be searched.")
    TAG (L"%%Learning rate%")
    DEFINITION (L"The rate at which the parameter neighborhood is shrunk (per iteration).")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers 1.1.2. Model selection@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Get accuracy estimate...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Estimate the classification accuracy of the selected @KNN classifier.")
    ENTRY (L"Arguments")
    TAG (L"%%Evaluation method%")
    DEFINITION (L"The method to be used for estimating the classification accuracy. Supported methods are 10-fold cross-validation and leave-one-out.")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@KNN & FeatureWeights: Get accuracy estimate...@")
    LIST_ITEM (L"@@KNN & Pattern & Categories: Evaluate...@")
    LIST_ITEM (L"@@KNN & Pattern & Categories & FeatureWeights: Evaluate...@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.2. Model selection@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END  
    
    MAN_BEGIN (L"KNN & FeatureWeights: Get accuracy estimate...", L"Ola S\\o\"der", 20080809 )
    INTRO (L"Estimate the classification accuracy of the @KNN classifier using the chosen @FeatureWeights.")
    ENTRY (L"Arguments")
    TAG (L"%%Evaluation method%")
    DEFINITION (L"The method to be used for estimating the classification accuracy. Supported methods are 10-fold cross-validation and leave-one-out.")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@KNN & Pattern & Categories: Evaluate...@")
    LIST_ITEM (L"@@KNN & Pattern & Categories & FeatureWeights: Evaluate...@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.2. Model selection@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END 
 
    
    MAN_BEGIN (L"KNN & Pattern & Categories: Evaluate...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Estimate the classification accuracy of the chosen @KNN classifier using the selected @Pattern and @Categories objects as test set.")
    ENTRY (L"Arguments")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@KNN & Pattern & Categories & FeatureWeights: Evaluate...@")
    LIST_ITEM (L"@@KNN: Get accuracy estimate...@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.2. Model selection@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END
    
    MAN_BEGIN (L"KNN & Pattern & Categories & FeatureWeights: Evaluate...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Estimate the classification accuracy of the chosen @KNN classifier using the selected @Pattern and @Categories objects as test set. The selected @FeatureWeights object will be used in the classification process.")
    ENTRY (L"Arguments")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@KNN & Pattern & Categories: Evaluate...@")
    LIST_ITEM (L"@@KNN: Get accuracy estimate...@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.2. Model selection@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Get size of instance base", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Queries the selected @KNN for the number of instances in the instance base. ")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Extract input Pattern", L"Ola S\\o\"der", 20080726 )
    INTRO (L"Create a new @Pattern object identical to the one in the instance base of the selected @KNN classifier.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Extract output Categories", L"Ola S\\o\"der", 20080726 )
    INTRO (L"Create a new @Categories object identical to the one in the instance base of the selected @KNN classifier.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Shuffle", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Shuffle the instance base of the selected classifier.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Prune...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Prune the instance base of the selected classifier.")
    ENTRY (L"Arguments")
    TAG (L"%%Noise pruning degree%")
    DEFINITION (L"A value in the range [0 ... 1] specifying the probability that instances tagged as noisy by @@kNN classifiers 1.2.1. Pruning|the C-Pruner algorithm@ will be pruned.")
    TAG (L"%%Redundancy pruning degree%")
    DEFINITION (L"The probability that instances tagged as redundant by @@kNN classifiers 1.2.1. Pruning|the C-Pruner algorithm@ will be pruned.")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers 1.2.1. Pruning@")
    LIST_ITEM (L"@@kNN classifiers 1.2. Improving resource efficiency@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: Reset...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Empty the instance base of the selected classifier.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN: To FeatureWeights...", L"Ola S\\o\"der", 20080728 )
    INTRO (L"Wrap the selected @KNN and use its feedback to guide the search for the optimal feature weights. A @FeatureWeights object will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%Learning rate%")
    DEFINITION (L"The rate at which the maximum distance between the pivot and a random seed is decremented.")
    TAG (L"%%Number of seeds%")
    DEFINITION (L"The size of the feature weight neighborhood.")
    TAG (L"%%Stop at%")
    DEFINITION (L"A value specifying a stopping criterion. When feature weights yielding accuracy estimates higher than the specified value the search will stop. A value of 1 imposes no constraints whereas a value of 0.5 will result in the termination of the search algorithm once feature weights resulting in an classification accuracy of 50 percent or better are found.")
    TAG (L"%%Optimization%")
    DEFINITION (L"Specifies whether to search for all features simultaneously or one at a time.")
    TAG (L"%%Evaluation method%")
    DEFINITION (L"The method to be used for estimating the classification accuracy. Supported methods are 10-fold cross-validation and leave-one-out.")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood used for feedback classification.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.2. Wrapper-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@KNN & Pattern & Categories & FeatureWeights: Evaluate...@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"KNN & Pattern & Categories: To FeatureWeights...", L"Ola S\\o\"der", 20080809 )
    INTRO (L"Wrap the selected @KNN and use its classification accuracy on the test set constituted by the @Pattern and @Categories objects as feedback to guide the search for the optimal feature weights. A @FeatureWeights object will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%Learning rate%")
    DEFINITION (L"The rate at which the maximum distance between the pivot and a random seed is decremented.")
    TAG (L"%%Number of seeds%")
    DEFINITION (L"The size of the feature weight neighborhood.")
    TAG (L"%%Stop at%")
    DEFINITION (L"A value specifying a stopping criterion. When feature weights yielding accuracy estimates higher than the specified value the search will stop. A value of 1 imposes no constraints whereas a value of 0.5 will result in the termination of the search algorithm once feature weights resulting in an classification accuracy of 50 percent or better are found.")
    TAG (L"%%Optimization%")
    DEFINITION (L"Specifies whether to search for all features simultaneously or one at a time.")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood used for feedback classification.")
    TAG (L"%%Vote weighting%")
    DEFINITION (L"The type of vote weighting to be used.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.2. Wrapper-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1. Improving classification accuracy@")
    LIST_ITEM (L"@@KNN & Pattern & Categories & FeatureWeights: Evaluate...@")
    LIST_ITEM (L"@@kNN classifiers 1. What is a kNN classifier?@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END


    MAN_BEGIN (L"Pattern & Categories: To FeatureWeights...", L"Ola S\\o\"der", 20080809 ) 
    INTRO (L"Compute an estimate of the optimal feature weights using the @@kNN classifiers 1.1.1.1. Filter-based feature weighting|RELIEF-F algorithm@.")
    TAG (L"%%k neighbors%")
    DEFINITION (L"The size of the neighborhood.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.1. Filter-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1.2. Wrapper-based feature weighting@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END



    MAN_BEGIN (L"Pattern: To Categories...", L"Ola S\\o\"der", 20080728 )
    INTRO (L"Split the given @Pattern into a fixed number of clusters using the @@k-means clustering|%%k%-means clustering algorithm@. A @Categories object containing numbered categories corresponding to the generated clusters will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%k clusters%")
    DEFINITION (L"The number of clusters to be generated.")
    TAG (L"%%Cluster size ratio constraint%")
    DEFINITION (L"The minimum allowed ratio between the smallest and the biggest cluster.")
    TAG (L"%%Maximum number of reseeds%")
    DEFINITION (L"The maximum allowed number of reseeds used to enforce the cluster size ratio constraint.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"Pattern & FeatureWeights: To Categories...", L"Ola S\\o\"der", 20080728 )
    INTRO (L"Split the given @Pattern into a fixed number of clusters using the @@k-means clustering|%%k%-means clustering algorithm@ and the feature weights contained within the selected @FeatureWeights object. A @Categories object containing numbered categories corresponding to the generated clusters will be created.")
    ENTRY (L"Arguments")
    TAG (L"%%k clusters%")
    DEFINITION (L"The number of clusters to be generated.")
    TAG (L"%%Cluster size ratio constraint%")
    DEFINITION (L"The minimum allowed ratio between the smallest and the biggest cluster.")
    TAG (L"%%Maximum number of reseeds%")
    DEFINITION (L"The maximum allowed number of reseeds used to enforce the cluster size ratio constraint.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@kNN classifiers@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    MAN_END

    
    MAN_BEGIN (L"Pattern: To Dissimilarity...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Generate a @Dissimilarity matrix from the selected @Pattern. Dissimilarities are computed using the @@Euclidean distance@")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@Multidimensional scaling@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END

    MAN_BEGIN (L"Pattern & FeatureWeights: To Dissimilarity...", L"Ola S\\o\"der", 20080718 )
    INTRO (L"Generate a @Dissimilarity matrix from the selected @Pattern using the feature weights contained within the selected @FeatureWeights object. Dissimilarities are computed using the @@Euclidean distance@.")
    ENTRY (L"See also:")
    LIST_ITEM (L"@@Multidimensional scaling@")
    LIST_ITEM (L"@@kNN classifiers 1.1.1. Feature weighting@")
    LIST_ITEM (L"@@kNN classifiers@")
    MAN_END


    /*

    MAN_BEGIN (L"kNN classifiers 2. Quick start", L"Ola S\\o\"der", 20080529)
    ENTRY (L"Creating a kNN classifier")
    NORMAL (L"A kNN classifier can be created by selecting #New \\=> ##kNN classifiers# \\=> ##Create kNN classifier# in the ##Praat objects# window. A form prompting for a name of the newly created classifier will be shown.")

    NORMAL (L"An alternative way of creating a kNN classifier is to select a @Pattern object and a @Categories object and choose ##To kNN classifier...#. The number of rows in the @Pattern object must match the number of categories in the @Categories object otherwise the creation of the classifier will fail.")

    NORMAL (L"Besides prompting for a name the shown form lets the user specify the ordering of the instances in the instance base to be created. If ##random# is selected the input data will be stored in random order, if ##sequential# is chosen the instance base will retain the order set by the input data. If the input data is sorted by category, sequential learning can lead to misleading accuracy estimates if accuracy is estimated by means of 10-fold cross validation. By choosing ##random# this is avoided. If the training data is already shuffled or if the learning phase is time critical (sequential learning is faster) ##sequential# might be the best choice.")


    ENTRY (L"Training")
    NORMAL (L"Unless the classifier is created by the selection of a @Pattern object and a @Categories object and choosing \"To kNN classifier...\" the classifier must be feed with training data in order to function. This is done by selecting the \"KNN\" object, a \"Pattern\" object and a \"Categories\" object and then selecting \"Learn...\". The form mentioned above (see Creating a kNN classifier) will prompt for a name and the ordering in which the instances will be inserted in the instance base. ")
    NORMAL (L"If the above is done using an already trained kNN classifier then the option of replacing the current instance base or appending the training data to the current instance base will be given. This will only succeed if the number of features in the old instance base and the number of features in the training data match.")


    ENTRY (L"Classification")
    NORMAL (L"A #KNN object can be used for classification by selecting the classifier object and a @Pattern object and choosing either ##To Categories...# or ##To TableOfReal...#. By choosing ##To Categories...# and setting the classifier parameters (a form prompting for the value of %k and the type of vote weighting to be used will be shown) a @Categories object containing the class labels of the input data will be created. If ##To TableOfReal...# is chosen then a #TableOfReal object containing information regarding the process of decision will be generated. Apart from the winning class label, the #TableOfReal object contains information on the number same-class instances within the neighborhood (defined by %k) and the average distance to these. It also contains information representing the probability that the current classification is correct. Two probability values are given, one where the within-neighborhood distances are taken into account, given that vote weighting is used, and one where all instances within the neighborhood are considered equally significant. The form shown upon choosing ##To TableOfReal...# will, on top of the standard classifier parameters, prompt for a value of the binary parameter labeled #Output. If ##Winners only# is set then only information regarding the winning category will be written to the ##TableOfReal# object. If ##All candidates# are chosen then information regarding all instances in the neighborhood will be written to the ##TableOfReal# object, where classification of a single input instance can be identified by the summing of the probability values of the output categories.")



    ENTRY (L"Evaluation")
    NORMAL (L"The accuracy of a classifier can be estimated by selecting the classifier object and ##Query - # \\=> ##Get accuracy estimate...#. A form prompting for model parameters and estimation method (10-fold cross validation/Leave-one-out) will be shown. If the classifier is selected together with an @FeatureWeights object then the estimate will be made using the feature weights contained within the \"FeatureWeights\" object.")
    NORMAL (L"The accuracy estimate can also be computed using a separate test set. In order to do so select the classifier, a \"Pattern\" object and a \"Categories\" object and choose \"Evaluate...\". The form shown will equal the one described above except for the absence of the estimation method options. If an \"FeatureWeights\" object is selected together with the classifier and the test set the contained feature weights will be used.")

    ENTRY (L"Feature weighting")
    NORMAL (L"The approximation of feature weights can be done by selecting a kNN classifier object and choosing \"To FeatureWeights...\". The form shown will prompt for quite a few parameters, where the most significant ones are \"Learning rate.\", \"Number of seeds\" and \"Stop at\".")
    NORMAL (L"The learning rate specifies how quickly the algorithm will home in on the final result, a lower value will generally, at the price of longer processing times, result in a better approximation of the global maximum. Valid values of the learning rate are 0 (exclusive) ... 1 (inclusive), where values near 1 make little sense.")
    NORMAL (L"The number of seeds specifies the size of the neighborhood used in the local search. A bigger neighborhood generally results in a more reliable outcome. The drawback of a high number of seeds is increased processing times.")
    NORMAL (L"The \"Stop at\" parameter constitutes a bound on the model accuracy estimate done by means of either 10-fold cross validation or leave-one-out. A value of 1 imposes no restrictions on the approximated accuracy, whereas as value of 0.5 will result in the algorithm stopping if weights resulting in an approximated accuracy equal to, or above, 50 percent are found. ")
    NORMAL (L"The \"Optimization\" option lets the user specify whether the algorithm shall search for one feature weight at a time or do a complete search for all feature weights simultaneously.")
    NORMAL (L"The remaining parameters control the evaluation of the found weights. Apart from the evaluation method options (10-fold cross validation and leave-one-out) the customary KNN model parameters can be specified.")



    ENTRY (L"Pruning")
    NORMAL (L"The instance base of a kNN classifier can be pruned by selecting the classifier object and choosing \"Modify -\" \\=> \"Prune...\". A form prompting for the degree of pruning (noise and redundancy) and a value of the parameter %k will be shown. A pruning degree of 1 means that the algorithm will, with 100 percent certainty, prune an instance tagged for pruning. A pruning degree of 0.5 will %on %average result in the retaining of 50 percent of the instances tagged as prunable. The value of %k is normally chosen to equal the value selected for classification.")

    ENTRY (L"Misc")
    NORMAL (L"The features listed below are normally of little value when P\\s{RAAT} is used in interactive mode. Their intended primary use is as utility functions in P\\s{RAAT} scripts.")
    LIST_ITEM (L"\\bu The size of the instance base of a classifier can be probed by selecting the classifier object and choosing \"Query -\" \\=> \"Get size of instance base\". ")
    LIST_ITEM (L"\\bu The instance base of a classifier can be shuffled by selecting the classifier object and choosing \"Modify -\" \\=> \"Shuffle\".")
    LIST_ITEM (L"\\bu All instances in the instance base of a classifier can be deleted by selecting the classifier object and choosing \"Modify -\" \\=> \"Reset...\".")
    LIST_ITEM (L"\\bu The @Pattern object containing the vectors representing the instances of a classifier can be extracted by selecting the classifier object and choosing \"Extract -\" \\=> \"Extract input Patterns\".")
    LIST_ITEM (L"\\bu The @Categories object representing the classes of the individual instances in the instance base can be extracted by selecting the classifier object and choosing \"Extract -\" \\=> \"Extract output Categories\".")
    MAN_END





    */

    MAN_BEGIN (L"Ke-Ping Zhao et al. (2003)", L"Ola S\\o\"der", 20080718)
    NORMAL (L"Ke-Ping Zhao et al. C-Pruner: An improved instance pruning algorithm. In %%Proceedings of the Second International Conference on Machine Learning and Cybernetics%, pages 94-99, November 2003.")
    MAN_END

    MAN_BEGIN (L"Igor Kononenko (1994)", L"Ola S\\o\"der", 20080718)
    NORMAL (L"Igor Kononenko. Estimating attributes: Analysis and extensions of relief. In %%ECML-94: Proceedings of the European Conference on Machine Learning, pages 171-182, Secaucus, NJ, USA, 1994. Springer-Verlag New York, Inc.")
    MAN_END

}

/* End of file manual_KNN.c */
