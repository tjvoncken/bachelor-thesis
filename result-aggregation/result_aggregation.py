from helper import computeAvgPerGenForName
#TODO: for each set or results:
    #TODO: compute avg score per generation.
    #TODO: compute avg score per ms.

# Results for 100 gens with f1 - L-System.
computeAvgPerGenForName("results/shortest-distance/100/", "systems", 10000, 104)
# Results for 100 gens with f1 - Token String.
computeAvgPerGenForName("results/shortest-distance/100/", "tokens", 10000, 104)

# Results for 100 gens with f2 - L-System.
computeAvgPerGenForName("results/total-distance/100/", "systems", 10000, 104)
# Results for 100 gens with f2 - Token String.
computeAvgPerGenForName("results/total-distance/100/", "tokens", 10000, 104)

# Results for 100 gens with f3 - L-System.
computeAvgPerGenForName("results/relative-distance/100/", "systems", 10000, 104)
# Results for 100 gens with f3 - Token String.
computeAvgPerGenForName("results/relative-distance/100/", "tokens", 10000, 104)

# Results for 500 gens with f1 - L-System.
computeAvgPerGenForName("results/shortest-distance/500/", "systems", 1000, 104)
# Results for 500 gens with f1 - Token String.
computeAvgPerGenForName("results/shortest-distance/500/", "tokens", 1000, 104)

# Results for 500 gens with f2 - L-System.
computeAvgPerGenForName("results/total-distance/500/", "systems", 1000, 104)
# Results for 500 gens with f2 - Token String.
computeAvgPerGenForName("results/total-distance/500/", "tokens", 1000, 104)

# Results for 500 gens with f3 - L-System.
computeAvgPerGenForName("results/relative-distance/500/", "systems", 1000, 104)
# Results for 500 gens with f3 - Token String.
computeAvgPerGenForName("results/relative-distance/500/", "tokens", 1000, 104)