# 第 8 章 - 模組

## 設計自己的模組

### 模組定義與引用

當您用 javascript 寫出物件或函式庫時，可以提供給其他程式使用。

在 node.js 當中，模組的定義大致有兩種類型，一種是「匯出物件」的靜態模組，另一種是匯出「建構函數」的動態模組。

### 靜態模組：匯出物件

以下是一個匯出物件的靜態模組定義。

模組定義：math.js

```javascript
var math = {
    PI:3.14,
    square:function(n) {
        return n*n;
    }
}

module.exports = math;

```

接著您可以使用 require 這個指令動態的引入該模組，注意 require 必須採用相對路徑，即使在同一個資料夾底下，也要加上 ./ 的前置符號，代表在目前資料夾之下。以下是一個引用上述模組的範例。

模組使用：mathTest.js

```javascript
var m=require("./math");

console.log("PI=%d square(3)=%d", m.PI, m.square(3));
```

執行結果：

```
D:\Dropbox\Public\pmag\201306\code>node mathTest
PI=3.14 square(3)=9

```

## 亂數模組

檔案： randomLib.js

```
var o={};

o.random = function(a,b) { 
  return a+Math.random()*(b-a); 
}

o.randomInt = function(a,b) { 
  return Math.floor(o.random(a,b)); 
}

o.sample = function(array) { 
  return array[o.randomInt(0,array.length)]; 
}

module.exports = o;
```

自動產生小學數學問題的程式

```
var R=require("./randomLib");
/*
問題:   小華有6個蘋果
        給了大雄3個
        又給了小明2個
        請問小華還有幾個蘋果?

答案:   1個
*/
var peoples = ["小明", "小華", "小莉", "大雄"];
var objects = ["蘋果", "橘子", "柳丁", "番茄"];
var owner = People();
var object = Object();
var nOwn = R.randomInt(3, 20);

remove(peoples, owner);

function remove(array, item) {
  array.splice(array.indexOf(item), 1); 
}

function MathTest() {
  return "問題:\t"+Own()+"\n\t"+Give()
         +"\n\t又"+Give()+"\n\t"+Question();
}

function Own() {
  return owner+"有"+nOwn+"個"+object;
}

function Give() {
  var nGive = R.randomInt(1, nOwn);
  nOwn-=nGive;
  return "給了"+People()+nGive+"個";
}

function Question() {
  return "請問"+owner+"還有幾個"+object+"?";
}

function People() {
  return R.sample(peoples);
}

function Object() {
  return R.sample(objects);
}

console.log(MathTest());
console.log("\n答案:\t"+nOwn+"個");
```

執行結果

```
D:\Dropbox\cccwd2\file\jsh\code\module>node genMath.js
問題:   小華有10個橘子
        給了大雄9個
        又給了小明1個
        請問小華還有幾個橘子?

答案:   0個

D:\Dropbox\cccwd2\file\jsh\code\module>node genMath.js
問題:   小明有18個橘子
        給了大雄11個
        又給了小華4個
        請問小明還有幾個橘子?

答案:   3個

```

### 物件模組：匯出建構函數

以下是一個定義圓形 circle 的物件。

模組定義：circle.js

```javascript
var PI = 3.14;
Circle = function (radius) {
    this.radius = radius
    this.area = function() {
        return PI * this.radius * this.radius;
    }
};

module.exports = Circle;
module.exports.PI = PI;

```

在引用「匯出建構函數」的程式當中，由於取得的是建構函數，因此必須再使用 new 的方式建立物件之後才能使用 
(例如以下的 `c = new cir(5)` 這個指令，就是在透過建構函數 `cir()` 建立物件。

模組使用：CircleTest.js

```javascript
var cir = require('./circle');  			// 注意，./ 代表 circle 與此程式放在同一個資料夾底下。
var c = new cir(5);
console.log("cir.PI="+cir.PI);
console.log("c.PI="+c.PI);
console.log("c.area()="+c.area());

```

執行結果

```
D:\code\node>node circleTest.js
cir.PI=3.14
c.PI=undefined
c.area()=78.5
```

您現在應該可以理解為何我們要將 Circle 定義為一個函數了吧！這只不過 Circle 類別的建構函數而已，
當他被 module.exports = Circle 這個指令匯出時，就可以在 var cir = require('./circle') 這個指令
接收到建構函數，然後再利用像 `var c = new cir(5)` 這樣的指令，呼叫該建構函數，以建立出物件。

然後，您也應該可以看懂為何我們要用 module.exports.PI = PI 將 PI 獨立塞到 module.exports 裏了吧！
因為只有這樣才能讓外面的模組在不執行物件建構函數 (不建立物件) 的情況之下就能存取 PI。

### 跨平台模組：定義各種平台均能使用的 JavaScript 模組

在很多開放原始碼的 JavaScript 專案模組中，我們會看到模組的最後有一段很複雜的匯出動作。舉例而言，
在 marked.js 這個將 Markdown 語法轉為 HTML 的模組最後，我們看到了下列這段感覺匪夷所思的匯出橋段，
這種寫法其實只是為了要讓這個模組能夠順利的在「瀏覽器、node.js、CommonJS 與其 Asynchronous 
Module Definition (AMD) 實作版的 RequireJS」等平台當中都能順利的使用這個模組而寫的程式碼而已。

```javascript

/**
 * Expose
 */

marked.Parser = Parser;
marked.parser = Parser.parse;

marked.Lexer = Lexer;
marked.lexer = Lexer.lex;

marked.InlineLexer = InlineLexer;
marked.inlineLexer = InlineLexer.output;

marked.parse = marked;

if (typeof exports === 'object') {
  module.exports = marked;
} else if (typeof define === 'function' && define.amd) {
  define(function() { return marked; });
} else {
  this.marked = marked;
}

}).call(function() {
  return this || (typeof window !== 'undefined' ? window : global);
}());
```

對這個超複雜匯出程式有興趣的朋友可以看看以下的文章，應該就可以大致理解這種寫法的來龍去脈了。

* <http://www.angrycoding.com/2012/10/cross-platform-wrapper-function-for.html>

## 用 npm 安裝外部套件

使用 npm install 可以安裝套件，舉例而言，假如我們有一個程式 main.js 用到 lodash 套件，其原始碼如下：

檔案： main.js

```javascript
var _=require("lodash");

var set=_.intersection([1,3,7,9], [2,3,8,9]);
console.log("set=", set);
```

我們想要執行這個程式，於是切到 main.js 所在的資料夾後打入 node main.js ，結果卻發現下列情況。

```
nqu-192-168-61-142:package mac020$ ls
main.js
nqu-192-168-61-142:package mac020$ node main.js
module.js:338
    throw err;
    ^

Error: Cannot find module 'lodash'
    at Function.Module._resolveFilename (module.js:336:15)
    at Function.Module._load (module.js:286:25)
    at Module.require (module.js:365:17)
    at require (module.js:384:17)
    at Object.<anonymous> (/Users/mac020/Dropbox/cccwd/db/js1/code/package/main.js:1:69)
    at Module._compile (module.js:434:26)
    at Object.Module._extensions..js (module.js:452:10)
    at Module.load (module.js:355:32)
    at Function.Module._load (module.js:310:12)
    at Function.Module.runMain (module.js:475:10)

```

這代表我們沒有安裝 lodash 套件，因此我們必須要用下列 npm 指令先安裝 lodash 套件。

```
nqu-192-168-61-142:package mac020$ npm install lodash
lodash@4.6.1 node_modules/lodash

nqu-192-168-61-142:package mac020$ ls
main.js		node_modules

nqu-192-168-61-142:package mac020$ ls node_modules
lodash
```

這樣就安裝好該套件了，您可以用 ls 列出目前資料夾內容，會發現多出的一個 node_modules 的資料夾，裡面會有 lodash 子資料夾，這代表您已經安裝好了該套件。

接著我們就可以用 node main.js 指令執行原本的程式，這樣就不會再產生錯誤了！

``` 
nqu-192-168-61-142:package mac020$ node main.js
set= [ 3, 9 ]
```

以上就是在 node.js 裏用 npm 安裝外部套件的做法！

## 發佈自己的套件 - 以 rlab 為例

Node.js 中的 JavaScript 模組，可以透過 npm 進行管理與發佈，方法是你必須撰寫 package.json 這個檔案來描述你的專案。

記得先查查有沒有名稱衝突

* <https://www.npmjs.com/search?q=rlab>

沒有衝突才能發佈成功

接著您必須為該模組撰寫或產生 package.json 專案檔，以下是我所撰寫的一個 rlab 模組之 package.json 專案檔範例：

檔案： package.json

```
{
  "name": "rlab",
  "version": "0.0.1",
  "description": "Javascript scientific library like R based on lodash",
  "main": "rlab.js",
  "dependencies": {
    "lodash": "^4.6.1"
  },
  "devDependencies": {},
  "scripts": {},
  "repository": {},
  "keywords": [],
  "author": "ccckmit",
  "license": "BSD-3-Clause",
  "homepage": "https://github.com/ccckmit/rlab"
}

```

寫好後和你的程式放在同一個資料夾下，接著就可以發佈初版，以下是我的上傳發布範例：

```
$ npm set init.author.name "ccckmit"
$ npm set init.author.email "ccckmit@gmail.com"
$ npm set init.author.url "http://ccc.nqu.edu.tw"
$ npm adduser
$ ls
$ npm init
$ npm install -g pakmanager
$ sudo npm install -g pakmanager
$ npm publish ./
```

當您已經發布成功之後，可以上 npm 網站在檢查看看是否可以查到你的專案。

* <https://www.npmjs.com/search?q=rlab>


如果專案有任何修改要再次發布，就可以用 npm version 指令更新版本，然後再用 npm publish 指令發布新版：

```
$ npm version 0.0.2
v0.0.2
$ npm publish ./
+ rlab@0.0.2
```

最後你可以用下列指令安裝自己的套件，並開始使用此套件！

```
nqu-192-168-61-142:js mac020$ npm install rlab
rlab@0.0.2 node_modules/rlab
└── lodash@4.6.1
nqu-192-168-61-142:js mac020$ node rtest
x=[1,3,2,6,3,2,5,4,4,3] max=6 min=1 mean=3.3
x= [ 20, 50, 10, 0, 80, 60, 70, 30, 100, 90 ]
```

您也可以在 package.json 當中加入像 github 專案的網址，這樣可以讓人家直接在網路上檢視你的原始碼，而且更方便多人一起共同合作開發：

以下是我使用 git 版本管理後上傳到 github 的一小段過程，更詳細的 git 使用請參考相關文獻。

```
nqu-192-168-61-142:rlab mac020$ git commit -am "add jStat functions"
[master 41cdba8] add jStat functions
 2 files changed, 24 insertions(+), 0 deletions(-)
nqu-192-168-61-142:rlab mac020$ git push -u origin master
Username: 
Password: 
Counting objects: 7, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 835 bytes, done.
Total 4 (delta 2), reused 0 (delta 0)
To https://github.com/ccckmit/rlab.git
   5a4adbf..41cdba8  master -> master
Branch master set up to track remote branch master from origin.
nqu-192-168-61-142:rlab mac020$ npm version 0.0.3
v0.0.3
```

如果要將 Node.js 的程式轉成可以在瀏覽器中使用的模組，可以利用 browserify 這個工具，browserify會將你的程式打包後變成單一的 javascript 檔案，並且去除 require 這類 node.js 專有的語法，讓你的程式可以順利的在瀏覽器當中執行。(當然、你的程式裡不可以呼叫那些不能在瀏覽器當中使用的函數，像是存取檔案系統等等)

以下《十分鐘系列》投影片詳細介紹了如何用 npm 創建並發布模組的方法，請您進一步閱讀以便學習這套非常方便且重要的方法。

* [用十分鐘瞭解JavaScript的模組 -- 《還有關於npm套件管理的那些事情》](https://www.slideshare.net/ccckmit/javascript-npm)


## 習題
1. 請設計一個自己寫的模組，並上傳到 npm 官網上。(如果你不知道該設計甚麼，那就把本章的 randomLib.js 拿來上傳到 npm 官網上好了)

