function find_min_combi(numberOfLocks, initCombi, unlockCombi){
    let minimumSteps = 0;
    while(numberOfLocks > 0){
        let biggerNum = Math.max(initCombi % 10, unlockCombi % 10);
        let smallerNum = Math.min(initCombi % 10, unlockCombi % 10);
        minimumSteps += Math.min(Math.abs(biggerNum - smallerNum), Math.abs((biggerNum - 10) - smallerNum));
        initCombi = Math.trunc(initCombi / 10);
        unlockCombi = Math.trunc(unlockCombi / 10);
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
        numberOfLocksRandom = Math.floor(Math.random() * 100) + 1;
        initCombiRandom = Math.floor(Math.random() * 10 ** numberOfLocksRandom);
        unlockCombiRandom = Math.floor(Math.random() * 10 ** numberOfLocksRandom); 
        // console.log(i + ": " + numberOfLocksRandom + " " + initCombiRandom + " " + unlockCombiRandom);
        find_min_combi(numberOfLocksRandom, initCombiRandom, unlockCombiRandom);
    }
    endTime = performance.now();
    runtimeDiffLength = endTime - startTime;

    return [runtimeSameLength, runtimeDiffLength];
}

function main(){
    // User Input
    // let numberOfLocks = prompt("Number of locks: ");
    // let initCombi = prompt("Initial configuration: ");
    // let unlockCombi = prompt("Unlock configuration: ");

    // Program Input
    let numberOfLocks = "4";
    let initCombi = "1234";
    let unlockCombi = "9899";
    
    let minCombi, runtimeProfiler;
    
    if(numberOfLocks != initCombi.length || numberOfLocks != unlockCombi.length){
        console.log("ERROR: Input mismatch in number of locks");
        return;
    }
    minCombi = find_min_combi(numberOfLocks, initCombi, unlockCombi);
    runtimeProfiler = runtime_profiler(numberOfLocks, initCombi, unlockCombi);

    console.log("*********************************************************");
    console.log();
    console.log("CoE 163 SE01: Profiling and Assembly (JavaScript)");
    console.log();
    console.log("Input:                                 " + numberOfLocks + " " + initCombi + " " + unlockCombi);
    console.log("Output:                                " + minCombi);
    console.log("Runtime (Case 1: Same Inputs):         " + runtimeProfiler[0].toFixed(4) + " ms");
    console.log("Runtime (Case 2: Randomized Inputs):   " + runtimeProfiler[1].toFixed(4) + " ms");
    console.log();
    console.log("NOTE: Leading zeroes are considered in runtime profiling");
    console.log();
    console.log("*********************************************************");
}

main();