function find_min_combi(numberOfLocks, initCombi, unlockCombi){
    if(numberOfLocks == 0) return 0;
    let minimumSteps = Math.min(Math.abs(unlockCombi % 10 - initCombi % 10), Math.abs((unlockCombi % 10 - 10) - initCombi % 10));
    return minimumSteps + find_min_combi(numberOfLocks - 1, (initCombi / 10) | 0, (unlockCombi / 10) | 0);
}

function runtime_profiler(numberOfLocks, initCombi, unlockCombi){
    let startTime, endTime, runtimeSameLength, runtimeDiffLength;

    startTime = performance.now();
    for(let i = 0; i < 1000; i++)
        find_min_combi(numberOfLocks, initCombi, initCombi);
    endTime = performance.now();
    runtimeSameLength = endTime - startTime;

    startTime = performance.now();
    for(let i = 0; i < 1000; i++)
        find_min_combi(numberOfLocks, initCombi, unlockCombi);
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