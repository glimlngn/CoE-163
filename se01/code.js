function find_min_combi(numberOfLocks, initCombi, unlockCombi){
    let minimumSteps = 0;
    while(numberOfLocks > 0){
        let biggerNum = Math.max(initCombi % 10, unlockCombi % 10);
        let smallerNum = Math.min(initCombi % 10, unlockCombi % 10);
        minimumSteps += Math.min(Math.abs(biggerNum - smallerNum), Math.abs((biggerNum - 10) - smallerNum));
        initCombi = (initCombi / 10) | 0;
        unlockCombi = (unlockCombi / 10) | 0;
        numberOfLocks--;
    }
    return minimumSteps;
}

function runtime_profiler(numberOfLocks, initCombi, unlockCombi){
    let startTime, endTime, numberOfLocksRandom, initCombiRandom, unlockCombiRandom, runtimeSameLength, runtimeDiffLength;

    startTime = performance.now();
    for(let i = 0; i < 1000; i++)
        find_min_combi(numberOfLocks, initCombi, unlockCombi);
    endTime = performance.now();
    runtimeSameLength = endTime - startTime;

    startTime = performance.now();
    for(let i = 0; i < 1000; i++){
        numberOfLocksRandom = Math.floor(Math.random() * 25) + 1; // find_min_combi doesn't yet output the correct value for N > 25
        initCombiRandom = Math.floor(Math.random() * 10 ** numberOfLocksRandom);
        unlockCombiRandom = Math.floor(Math.random() * 10 ** numberOfLocksRandom); 
        console.log("Random " + i + ": " + numberOfLocksRandom + " " + initCombiRandom + " " + unlockCombiRandom);
        console.log(find_min_combi(numberOfLocksRandom, initCombiRandom, unlockCombiRandom));
    }
    endTime = performance.now();
    runtimeDiffLength = endTime - startTime;

    return [runtimeSameLength, runtimeDiffLength];
}

function main(){
    let numberOfLocks = prompt("Number of locks: ");
    let initCombi = prompt("Initial configuration: ");
    let unlockCombi = prompt("Unlock configuration: ");
    let minCombi, runtimeProfiler;
    
    if(numberOfLocks != initCombi.length || numberOfLocks != unlockCombi.length){
        console.log("ERROR! Number of locks do not match lock configurations.");
        return;
    }

    minCombi = find_min_combi(numberOfLocks, initCombi, unlockCombi);
    console.log("Input: " + numberOfLocks + " " + initCombi + " " + unlockCombi);
    console.log("Output: " + minCombi);

    runtimeProfiler = runtime_profiler(numberOfLocks, initCombi, unlockCombi);

    console.log("Runtime Profiling (Same Length): " + runtimeProfiler[0].toFixed(4) + " ms");
    console.log("Runtime Profiling (Different Length): " + runtimeProfiler[1].toFixed(4) + " ms");
}

main();