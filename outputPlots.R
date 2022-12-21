library(ggplot2)

# read the datafile 
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputFacetWrap.csv",
                   header = F, sep = " ")
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/niceOutput.csv",
                   header = F, sep = " ")
myData <- read.csv("/Users/willemijnoudijk/Documents/STUDY/Master Biology/C++Course /miniProject/AgeingModel/AgeingModel/data/outputFacetWrap_min0_01_sd0_01.csv",
                   header = F, sep = " ")

colnames(myData) <- c("time", "age", "survivalProb") # set colnames 
colnames(myData) <- c("time", "mean", "sd", "extrinsicMort", "age", "survivalProb") # for only mean_sd_varied

# 1579802101 seed with tEnd = 100.000, mutProb = 0.2, totalPop = 100, meanMut = -0.001, sd = 0.01 
# use facet wrap to visualize survival probabilities over time for every age 

p<- ggplot(data = myData, aes(time, survivalProb)) + geom_line()
p + facet_wrap(vars(age))

ggplot(data = myData, aes(x = age, y = survivalProb, col = time, group = time)) + 
  geom_line() +
  scale_color_viridis_c(option = "A")

# to plot the life expectancy against the mutation bias 
myDataLE <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Debug/outputLE.csv",
                     header = F, sep = " ")
colnames(myDataLE) <- c("meanMutationEffect", "LifeExpectancyMales", "LifeExpectancyFemales") # set colnames 
coloursLegend <- c("LifeExpectancyMales" = "royalblue",
             "LifeExpectancyFemales" = "coral1")
ggplot() +
  geom_point(data = myDataLE, aes(x = meanMutationEffect, y = LifeExpectancyMales,
                                  colour = "LifeExpectancyMales")) +
  geom_point(data = myDataLE, aes(x = meanMutationEffect, y = LifeExpectancyFemales,
                                  colour = "LifeExpectancyFemales"), alpha = 0.3) +
  theme_bw() +
  labs(title = "The (mean) mutation bias and the life expectancy",
      subtitle = "per individual",
       x = "Mutation bias", 
       y = "Life expectancy (age)") +
  scale_color_manual(values = coloursLegend)

# different ouputs: 
# mean = -0.01
# sd = 0.01
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputFacetWrap_mean_min_0_01.csv",
                   header = F, sep = " ")
colnames(myData) <- c("time", "age", "survivalProb") # set colnames 

# 1579802101 seed with tEnd = 100.000, mutProb = 0.2, totalPop = 100, meanMut = -0.001, sd = 0.01 
# use facet wrap to visualize survival probabilities over time for every age 
p <- ggplot(data = myData, aes(time, survivalProb)) + geom_line()
p + facet_wrap(vars(age)) +
  ylim(0.8, 1)


# mean = -0.001
# sd = 0.001
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputFacetWrap_mean_min_0.001_sd_0_001.csv",
                   header = F, sep = " ")
colnames(myData) <- c("time", "age", "survivalProb") # set colnames 

# use facet wrap to visualize survival probabilities over time for every age 
p <- ggplot(data = myData, aes(time, survivalProb)) + geom_line()
p + facet_wrap(vars(age)) +
  ylim(0.9, 1)


# mean = -0.5
# sd = 0.01
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputFacetWrap_mean_min0_5.csv",
                   header = F, sep = " ")
colnames(myData) <- c("time", "age", "survivalProb") # set colnames 

# use facet wrap to visualize survival probabilities over time for every age 
p <- ggplot(data = myData, aes(time, survivalProb)) + geom_line()
p + facet_wrap(vars(age))


# mean = 0.01
# sd = 0.01
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputFacetWrap_mean_0_01.csv",
                   header = F, sep = " ")
colnames(myData) <- c("time", "age", "survivalProb") # set colnames 

# use facet wrap to visualize survival probabilities over time for every age 
p <- ggplot(data = myData, aes(time, survivalProb)) + geom_line()
p + facet_wrap(vars(age))

# death age 
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputDeathAge.csv",
                   header = F)
colnames(myData) <- c("time", "averageDeathAge")
ggplot(myData, aes(time, averageDeathAge)) + geom_point() # should increase over time 


# to visualize drift, a small population of 100 was used 
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputFacetWrap_DRIFT_smallPop.csv",
                   header = F, sep = " ")
colnames(myData) <- c("time", "age", "survivalProb") # set colnames 
p <- ggplot(data = myData, aes(time, survivalProb)) + geom_line()
p + facet_wrap(vars(age))







