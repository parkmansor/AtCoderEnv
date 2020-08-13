import { readFileSync } from 'fs'
import { reverse } from 'dns'
import { start } from 'repl'

function main(input: string[]) {
  let N = Number(input[0])
 
  // 26
  // 26 * 26 = 676        702
  // 26 * 26 * 26 = 17576 18278
  N--
  let startVal = 0
  let addVal = 26;
  while (1) {
    if (startVal <= N && N < startVal + addVal) {
      N -= startVal
      break;
    }
    startVal += addVal
    addVal *= 26
  }

  let ans = ""
  addVal /= 26
  while (1) {
    let ansOne = Math.floor(N / addVal)
    N -= ansOne * addVal
    ansOne += "a".charCodeAt(0)
    ans += String.fromCharCode(ansOne)
    if (addVal == 1) break
    addVal /= 26
  }
  // 18278 - 702 = 17576

  console.log(ans.toString())
}

let lines: string[] = [];
const reader = require('readline').createInterface({
  input: process.stdin,
  output: process.stdout
});

reader.on('line', function (line: string) {
  lines.push(line);
});
reader.on('close', function () {
  main(lines)
});
