import csv
import numpy

def computeAvgPerGenForName(name : str, type : str, maxGen : int, resultCount : int):
    """
    Computes the average score per generation for test with given name.
    Considers at most ${maxGen} generations.
    Looks for ${resultCount} results, in files numbered 0 to ${resultCount} - 1.
    """
    results = []
    for i in range(0, resultCount):
        filename = "{name}/{i}-{type}.csv".format(name=name, i=i, type=type);
        with open(filename, "r") as csvfile:
            reader = csv.reader(csvfile, delimiter=';', quotechar='"')
            localRes = []

            for [gen, time, score] in reader:
                # Cancel the for loop once maxGen has been passed.
                if int(gen) > maxGen: 
                    break

                localRes.append(int(score))

            results.append(localRes)

    # Aggregate the results.
    numArray = numpy.array(results);
    meanPerGen = numArray.mean(axis=0)
    stdDevPerGen = numArray.std(axis=0)

    # Write away the aggregated results.
    with open("{name}/avg-gen-{type}.csv".format(name=name, type=type), 'w') as output:
        output.write("gen;avg;stddev\n")
        for i in range(0, maxGen + 1):
            output.write("{gen};{avg};{std}\n".format(gen=i, avg=meanPerGen[i], std=stdDevPerGen[i]))