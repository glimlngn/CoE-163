// NOTE: Please run the code in Node.js. Thank you! 

function find_min_combi(numberOfLocks, initCombi, unlockCombi){     // has a lot of math functions
    let minimumSteps = 0;
    while(numberOfLocks > 0){   // loop goes through all digits of the lock
        let biggerNum = Math.max(initCombi % 10, unlockCombi % 10);    // decides placement of values for the following formula
        let smallerNum = Math.min(initCombi % 10, unlockCombi % 10);

        minimumSteps += Math.min(Math.abs(biggerNum - smallerNum), Math.abs((biggerNum - 10) - smallerNum));    // adds min. steps of digit, number wrapping is emulated
        
        initCombi = Math.trunc(initCombi / 10);     // iterates to the next digit (from right to left)
        unlockCombi = Math.trunc(unlockCombi / 10);
        numberOfLocks--;
    }
    return minimumSteps;    // returns minimum number of steps of the lock
}

function runtime_profiler(numberOfLocks, initCombi, unlockCombi){
    // NOTE: Leading zeroes are considered in runtime profiling.

    let startTime, endTime, numberOfLocksRandom, initCombiRandom, unlockCombiRandom, runtimeSameLength, runtimeDiffLength;

    // Case 1: Same Length
    // find_min_combi is iterated 1000 times with programmed input
    startTime = performance.now();
    for(let i = 0; i < 1000; i++)
        find_min_combi(numberOfLocks, initCombi, unlockCombi);
    endTime = performance.now();
    runtimeSameLength = endTime - startTime;

    // Case 2: Different Length
    // Similar to Case 1, but find_min_combi has randomized inputs with N number of D digits where N: 1 to 100, and D: 0 to 9
    startTime = performance.now();
    for(let i = 0; i < 1000; i++){
        numberOfLocksRandom = Math.floor(Math.random() * 100) + 1;
        initCombiRandom = Math.floor(Math.random() * 10 ** numberOfLocksRandom);
        unlockCombiRandom = Math.floor(Math.random() * 10 ** numberOfLocksRandom); 
        find_min_combi(numberOfLocksRandom, initCombiRandom, unlockCombiRandom);
        // console.log(i + ": " + numberOfLocksRandom + " " + initCombiRandom + " " + unlockCombiRandom);
        // console.log(find_min_combi(numberOfLocksRandom, initCombiRandom, unlockCombiRandom));
    }
    endTime = performance.now();
    runtimeDiffLength = endTime - startTime;

    return [runtimeSameLength, runtimeDiffLength];  // returns array of runtimes for both profiling cases
}

function main(){
    let numberOfLocks = "4";    // input
    let initCombi = "1234";
    let unlockCombi = "9899";
    
    let minCombi, runtimeProfiler;
    
    if(numberOfLocks != initCombi.length || numberOfLocks != unlockCombi.length){
        console.log("ERROR: Input mismatch in number of locks");    // exits program if error occurs
        return;
    }
    minCombi = find_min_combi(numberOfLocks, initCombi, unlockCombi);   // output
    runtimeProfiler = runtime_profiler(numberOfLocks, initCombi, unlockCombi);

    console.log("*********************************************************");   // prints everything in console
    console.log();
    console.log("CoE 163 SE01: Profiling and Assembly (JavaScript)");
    console.log();
    console.log("Input:                                 " + numberOfLocks + " " + initCombi + " " + unlockCombi);
    console.log("Output:                                " + minCombi);
    console.log("Runtime (Case 1: Same Length):         " + runtimeProfiler[0].toFixed(4) + " ms");
    console.log("Runtime (Case 2: Different Length):    " + runtimeProfiler[1].toFixed(4) + " ms");
    console.log();
    console.log("*********************************************************");
}

main();