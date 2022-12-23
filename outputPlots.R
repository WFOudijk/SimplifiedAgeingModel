# RSCRIPT: Simplified Ageing Model - Willemijn Oudijk - created 16 december 2022

library(ggplot2)

# params: 
# totalPopulation = 10.000
# initSurvProb = 0.95
# numOfOffspringPerFemale = 1
# mutationProb = 0.01
# extrinsicMortRisk = 0.05
# outputTime = 200
# tEnd = 10.000

# change path to your data folder 
path <- "/Users/willemijnoudijk/Documents/STUDY/Master Biology/C++Course /miniProject/AgeingModel/AgeingModel/data/"
# change path to where you want the plots to be outputted 
output_path <- "/Users/willemijnoudijk/Documents/STUDY/Master Biology/C++Course /miniProject/plots/"

######## default params ##########
# mean = -0.01 and sd = 0.01
myData <- read.csv(paste(path, "outputFacetWrap_mean_min_0_01_sd_0_01.csv", sep = ""),
                   header = F, sep = " ")
colnames(myData) <- c("time", "mean", "sd", "extrinsicMort", "age", "survivalProb") 
p <- ggplot(data = myData, aes(x = time, y = survivalProb)) + 
  geom_line() + scale_color_viridis_c(option = "A") + 
  labs(title = "The survival probability over time for all age classes", 
       subtitle = "with mean = -0.01 and standard deviation = 0.01",
       x = "Time",
       y = "Survival Probability") +
  theme(axis.text.x = element_text(angle = 90))
p + facet_wrap(vars(age))
# to save the plot 
ggsave(paste(output_path, "plot_default_params.pdf", sep = ""), plot = last_plot())

# same data, different visualization. Time is colouring. 
ggplot(data = myData, aes(x = age, y = survivalProb, col = time, group = time)) + 
  geom_line() +
  labs(title = "The survival probability for all age classes", 
       subtitle = "with mean = -0.01 and standard deviation = 0.01",
       x = "Age",
       y = "Survival Probability") +
  scale_color_viridis_c(option = "A")
ggsave(paste(output_path, "plot_default_params_2.pdf", sep = ""), plot = last_plot())

######## varying mu and sigma ##########
# mean, mu = -0.005 + repl * 0.003 (repl = 1:20)

######### sd = mean / 10 ###########
parent_path <- paste(path, "mean_sd_varied_20_reps/", sep = "")
f <- list.files(path = parent_path, pattern = "outputFacetWrap.csv", recursive = T)
found <- c()
for (x in f) {
  file_name <- paste0(parent_path, x)
  local_data <- read.csv(file_name, header = F, sep = " ")
  found <- rbind(found, local_data)
}
colnames(found) <- c("time", "mean", "sd", "extrinsicMort", "age", "survivalProb") # for only mean_sd_varied
p <- ggplot(data = found, aes(x = time, y = survivalProb, col = mean, group = mean)) + 
  geom_line() + scale_color_viridis_c(option = "A") + 
  labs(title = expression("Mutation bias (" * mu * 
                            ") = -0.044 ~ 0.01; Effect size (" * sigma * ") = |" * mu * " / 10|"), 
       x = "Time",
       y = "Survival Probability") +
  theme(axis.text.x = element_text(angle = 90))
p + facet_wrap(vars(age))
ggsave(paste(output_path, "plot_mean_sd_10.pdf", sep = ""), plot = last_plot()) #to save file 

######### sd = mean / 5 ##########
parent_path <- paste(path, "sd_div_5/", sep = "")
f <- list.files(path = parent_path, pattern = "outputFacetWrap.csv", recursive = T)
found <- c()
for (x in f) {
  file_name <- paste0(parent_path, x)
  local_data <- read.csv(file_name, header = F, sep = " ")
  found <- rbind(found, local_data)
}
colnames(found) <- c("time", "mean", "sd", "extrinsicMort", "age", "survivalProb") # for only mean_sd_varied

# original data for every time point 
p <- ggplot(data = found, aes(x = time, y = survivalProb, col = mean, group = mean)) + 
  geom_line() + scale_color_viridis_c(option = "A") + 
  labs(title = expression("Mutation bias (" * mu * 
                            ") = -0.044 ~ 0.01; Effect size (" * sigma * ") = |" * mu * " / 5|"),
       x = "Time",
       y = "Survival Probability") +
  theme(axis.text.x = element_text(angle = 90))
p + facet_wrap(vars(age))
ggsave(paste(path, "plot_varySD_mut_5.pdf", sep = ""), plot = last_plot()) #to save file 


######### sd = mean / 2 ##########
parent_path <- paste(path, "sd_div_2/", sep = "")
f <- list.files(path = parent_path, pattern = "outputFacetWrap.csv", recursive = T)
found <- c()
for (x in f) {
  file_name <- paste0(parent_path, x)
  local_data <- read.csv(file_name, header = F, sep = " ")
  found <- rbind(found, local_data)
}
colnames(found) <- c("time", "mean", "sd", "extrinsicMort", "age", "survivalProb") # for only mean_sd_varied

# original data for every time point 
p <- ggplot(data = found, aes(x = time, y = survivalProb, col = mean, group = mean)) + 
  geom_line() + scale_color_viridis_c(option = "A") + 
  labs(title = expression("Mutation bias (" * mu * 
                            ") = -0.044 ~ 0.01; Effect size (" * sigma * ") = |" * mu * " / 2|"),
       x = "Time",
       y = "Survival Probability") +
  theme(axis.text.x = element_text(angle = 90))
p + facet_wrap(vars(age))
ggsave(paste(path, "plot_varySD_mut_half.pdf", sep = ""), plot = last_plot()) #to save file 

############ sd = mean ###########
parent_path <- paste(path, "mean_equal_sd_varied_20_reps/", sep = "")
f <- list.files(path = parent_path, pattern = "outputFacetWrap.csv", recursive = T)
found <- c()
for (x in f) {
  file_name <- paste0(parent_path, x)
  local_data <- read.csv(file_name, header = F, sep = " ")
  found <- rbind(found, local_data)
}
colnames(found) <- c("time", "mean", "sd", "extrinsicMort", "age", "survivalProb") # for only mean_sd_varied

p <- ggplot(data = found, aes(x = time, y = survivalProb, col = mean, group = mean)) + 
  geom_line() + scale_color_viridis_c(option = "A") + 
  labs(title = expression("Mutation bias (" * mu * 
                            ") = -0.044 ~ 0.01; Effect size (" * sigma * ") = |" * mu * "|"), 
       x = "Time",
       y = "Survival Probability") +
  theme(axis.text.x = element_text(angle = 90))
p + facet_wrap(vars(age))
ggsave(paste(path, "plot_mean_sd_equal.pdf", sep = ""), plot = last_plot()) #to save file 

######### sd = mean * 10 ############
parent_path <- paste(path, "mean_sd_bigger_varied_20_reps/", sep = "")
f <- list.files(path = parent_path, pattern = "outputFacetWrap.csv", recursive = T)
found <- c()
for (x in f) {
  file_name <- paste0(parent_path, x)
  local_data <- read.csv(file_name, header = F, sep = " ")
  found <- rbind(found, local_data)
}
colnames(found) <- c("time", "mean", "sd", "extrinsicMort", "age", "survivalProb") # for only mean_sd_varied

p <- ggplot(data = found, aes(x = time, y = survivalProb, col = mean, group = mean)) + 
  geom_line() + scale_color_viridis_c(option = "A") + 
  labs(title = "The survival probability over time for all age classes", 
       subtitle = "with differing means, where standard deviation = mean * 10",
       x = "Time",
       y = "Survival Probability") +
  theme(axis.text.x = element_text(angle = 90))
p + facet_wrap(vars(age))
ggsave(paste(path, "plot_sd_bigger_mean.pdf", sep = ""), plot = last_plot()) #to save file 

######## set mean = -0.02 and sd = 0.01 ###############
####### varying extrinsic mortality ###############
# extrinsic mortality: repl (1:20) * 0.005 = 0.005 ~ 0.1

########## average age of death over extrinsic mortality probabolity ###############
parent_path <- paste(path, "extr_mort_report/", sep = "")

f <- list.files(path = parent_path, pattern = "outputDeathAge.csv", recursive = T)
found <- c()
for (x in f) {
  file_name <- paste0(parent_path, x)
  local_data <- read.csv(file_name, header = F, sep = " ")
  found <- rbind(found, local_data)
}
colnames(found) <- c("time", "mean", "sd", "extrinsicMort", "deathAge") 
# only look at final time point 
final_time <- subset(found, time == 9800)
ggplot(data = final_time, aes(x = extrinsicMort, y = deathAge)) + 
  geom_line() +
  scale_color_viridis_c(option = "A") +
  labs(x = "Extrinsic mortality",
       y = "Average age of death") 
ggsave(paste(output_path, "plot_vary_extr_mort_report.pdf", sep = ""), plot = last_plot()) #to save file 

############# life expectancy over extrinsic mortality probabolity ############
parent_path <- paste(path, "extr_mort_report/", sep = "")

f <- list.files(path = parent_path, pattern = "outputLE.csv", recursive = T)
found <- c()
for (x in f) {
  file_name <- paste0(parent_path, x)
  local_data <- read.csv(file_name, header = F, sep = " ")
  found <- rbind(found, local_data)
}
colnames(found) <- c("mean", "sd", "extrinsicMort", "MalesLE", "FemalesLE") 
meanLEs <- data.frame(matrix(nrow = 0, ncol = 3))
colnames(meanLEs) <- c("ExtrinsicMort", "AverageMaleLE", "AverageFemaleLE")
for (i in unique(found$extrinsicMort)){
  sub <- subset(found, extrinsicMort == i)
  meanMales <- mean(sub$MalesLE)
  meanFemales <- mean(sub$FemalesLE)
  meanLEs[nrow(meanLEs) + 1,] <- c(i, meanMales, meanFemales)
}

# to get the average per extrinsic mortality value for males and females combined 
averageMalesAndFemales <- rowMeans(meanLEs[, c(2, 3)])
ggplot(data = meanLEs, aes(x = ExtrinsicMort, y = averageMalesAndFemales)) + 
  geom_line() +
  scale_color_viridis_c(option = "A") +
  labs(x = "Extrinsic mortality",
       y = "Average life expectancy") 
ggsave(paste(path, "plot_life_exp_report.pdf", sep = ""), plot = last_plot()) 

