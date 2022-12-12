library(ggplot2)

# read the datafile 
myData <- read.csv("/Users/willemijnoudijk/Library/Developer/Xcode/DerivedData/AgeingModel-gddgkdzqixdlpqdakssjsiqxffsy/Build/Products/Release/outputFacetWrap.csv",
                   header = F, sep = " ")
colnames(myData) <- c("time", "age", "survivalProb") # set colnames 

# 1579802101 seed with tEnd = 100.000, mutProb = 0.2, totalPop = 100, meanMut = -0.001, sd = 0.01 
# use facet wrap to visualize survival probabilities over time for every age 
p <- ggplot(data = myData, aes(time, survivalProb)) + geom_line()
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






