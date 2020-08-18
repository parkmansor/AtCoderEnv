"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
function divCnt(n) {
    let ans = 0;
    for (let i = 1; i <= Math.sqrt(n); i++) {
        if (n % i == 0) {
            ans++;
            if (i * i != n) {
                ans++;
            }
        }
    }
    return ans;
}
function main(input) {
    let N = Number(input[0]);
    let ans = BigInt(0);
    // 1 : 1
    // 2 : 1 2
    // 3 : 1   3 
    // 4 : 1 2   4
    // 5 : 1        5
    // 6 : 1 2 3      6
    // 7 : 1            7
    // 8 : 1 2   4        8
    for (let i = 1; i <= N; i++) {
        let cnt = Math.floor(N / i);
        let ansOne = (cnt * (cnt + 1) / 2) * i;
        ans += BigInt(ansOne);
    }
    console.log(ans.toString());
}
let lines = [];
const reader = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout
});
reader.on('line', function (line) {
    lines.push(line);
});
reader.on('close', function () {
    main(lines);
});
//# sourceMappingURL=index.js.map