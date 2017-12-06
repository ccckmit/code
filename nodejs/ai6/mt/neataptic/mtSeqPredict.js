// ex: node mtPredict mtDog.json
var Lstm = require('./lstmMtSeq')
var fs = require('fs')

var lstmJson = fs.readFileSync(process.argv[2])
Lstm.fromJSON(lstmJson)
var s = ['一 隻 狗', '小 狗', '小 貓', '一 隻 小 貓']
for (let i = 0; i < s.length; i++) {
  Lstm.predict('↓ ' + s[i] + ' =')
}
