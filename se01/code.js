function find_min_combi(numberOfLocks, initCombi, unlockCombi){
    if(numberOfLocks == 0) return 0;
    let minimumSteps = Math.min(Math.abs(unlockCombi % 10 - initCombi % 10), Math.abs((unlockCombi % 10 - 10) - initCombi % 10));
    return minimumSteps + find_min_combi(numberOfLocks - 1, (initCombi / 10) | 0, (unlockCombi / 10) | 0);
}

function find_min_combi_1000(){

}

function main(){
    let numberOfLocks = prompt("Number of locks: ");
    let initCombi = prompt("Initial configuration: ");
    let unlockCombi = prompt("Unlock configuration: ");
    
    if(numberOfLocks != initCombi.length || numberOfLocks != unlockCombi.length){
        console.log("ERROR! Number of locks do not match lock configurations.");
        return;
    }

    console.log(numberOfLocks, initCombi, unlockCombi);
    console.log(find_min_combi(numberOfLocks, initCombi, unlockCombi));
}

main();