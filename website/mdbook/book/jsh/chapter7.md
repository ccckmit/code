# 第 7 章 - 函式庫


在本書中，我們使用 javascript 語言，並主要在 node.js 平台上進行測試與開發，因此使用到的函數褲可分為兩部分，一部分是 javascript 語言本身所附帶的基本函式庫。另一部分是 node.js 平台所提供的函式庫。


Javascript語言本身所附帶的標準函式庫數量不大，主要包含下列幾類。

* [JavaScript 的標準函式庫請參考 《JavaScript 标准参考教程（alpha）》，by 阮一峰](http://javascript.ruanyifeng.com/#stdlib)
 * [物件 Object](http://javascript.ruanyifeng.com/stdlib/object.html)
 * [陣列 Array](http://javascript.ruanyifeng.com/stdlib/array.html)
 * [封裝 Wrapper](http://javascript.ruanyifeng.com/stdlib/wrapper.html)
 * [數值 Number](http://javascript.ruanyifeng.com/stdlib/number.html)
 * [字串 String](http://javascript.ruanyifeng.com/stdlib/string.html)
 * [數學 Math](http://javascript.ruanyifeng.com/stdlib/math.html)
 * [正規表達式 Regexp](http://javascript.ruanyifeng.com/stdlib/regexp.html)
 * [JSON交換格式](http://javascript.ruanyifeng.com/stdlib/json.html)

而 node.js 平台所提供的函式庫，除了和網站設計有關的部分之外，還有一些是和輸出入有關的功能，這類輸出入功能是不能在瀏覽器內使用的，因此也沒有被包含到 JavaScript 的標準函式庫中，但在本書中我們會常常使用到，您可以從 node.js 官網當中閱讀有關這些函數的 API (Application Interface)

* node.js 的官方系統 API 位於
 * <https://nodejs.org/api/>

建議讀者可以花些時間看看上述這些比較常用且重要的函式庫，先瀏覽之後建立一點概念就行了，這樣等到你需要用到時，就會知道去哪裡找出你要的函數了。

除此之外，開放原始碼社群，像是 node.js 官方的 npm 套件管理器當中，還包含了數十萬個套件供您使用，因此我們可以使用的資源是非常多的。

當然、我們不可能把這些套件通通都看過，甚至連列出來都有困難，因此我們必須學習如何尋找出需要的套件，這樣的能力在這個開放原始碼主導的程式世界裏，變得愈來愈重要了！

接著、讓我們透過範例的方式，先介紹一些常用的函式庫與其用法給大家認識，就讓我們從《數學函式庫》開始吧！

## 數學函式庫

```
$ node 
> Math.E
2.718281828459045
> Math.PI
3.141592653589793
> Math.LN10
2.302585092994046
> Math.LN2
0.6931471805599453
> Math.abs(-1)
1
> Math.exp(3)
20.085536923187668
> Math.log(8)
2.0794415416798357
> Math.log(20)
2.995732273553991
> Math.sin(0)
0
> Math.cos(0)
1
> Math.sin(Math.PI/2)
1
> Math.sin(Math.PI/4)
0.7071067811865475
> Math.floor(3.14)
3
> Math.ceil(3.14)
4
> Math.log2(8)
3
> Math.round(3.4)
3
> Math.round(3.6)
4
> Math.pow(2,3)
8
> Math.pow(3,2)
9
> Math.random()
0.7020524246271729
> Math.random()
0.2477522623638886
> Math.random()
0.9461785962462068
```

## 亂數

```
var random = function(a,b) { 
    return a+Math.random()*(b-a); 
}

var randomInt = function(a,b) { 
    return Math.floor(random(a,b)); 
}

var sample = function(array) { 
    return array[randomInt(0,array.length)]; 
}

console.log("random(10,20)=", random(10,20));
console.log("randomInt(10,20)=", randomInt(10,20));
console.log("sample([a,b,c,d,e])=", sample(['a','b','c','d','e']));
```

執行

```
D:\Dropbox\cccwd2\file\jsh\code\lib>node random
random(10,20)= 19.358721433673054
randomInt(10,20)= 19
sample([a,b,c,d,e])= b
```
## 時間控制


JavaScript 內建的函數 setTimeOut() 是一個採用回呼方式設計的函數，以下是一個用回呼來印出時間的範例。

檔案： clock.js

```
function printTime() {
  console.log(new Date());
  setTimeout(printTime, 1000);
}

setTimeout(printTime, 1000);
```

執行結果

```
nqu-192-168-61-142:code mac020$ node clock
Mon Oct 12 2015 16:37:38 GMT+0800 (CST)
Mon Oct 12 2015 16:37:39 GMT+0800 (CST)
Mon Oct 12 2015 16:37:40 GMT+0800 (CST)
Mon Oct 12 2015 16:37:41 GMT+0800 (CST)
Mon Oct 12 2015 16:37:42 GMT+0800 (CST)
....
```

在上述的 printTime() 函數中，透過 setTimeout(printTime, 1000) 會在 1 秒之後再度呼叫 printTime() ，於是每隔 1 秒就會印出一次時間，這是一個結合遞迴與回呼的程式。


## 用 npm 安裝外部套件


除了預設的函式庫之外，我們也可以使用外部的套件。

在 node.js 當中，預設就有 npm (node package manager) 這個指令，可以用來管理、安裝、發布套件。

我們可以使用 npm install 指令安裝套件，舉例而言，假如我們有一個程式 main.js 用到 lodash 套件，其原始碼如下：

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

npm 目前已經有數十萬個套件可以供我們使用，您也可以自己定義套件，然後透過 npm publish 指令發布套件，以下《十分鐘系列》投影片詳細介紹了如何用 npm 創建並發布模組的方法，請您進一步閱讀以便學習這套非常方便且重要的方法。

* [用十分鐘瞭解JavaScript的模組 -- 《還有關於npm套件管理的那些事情》](https://www.slideshare.net/ccckmit/javascript-npm)

## 習題
1. 請寫一個函數，可以產生 n 個 a 到 b 之間的的整數亂數，並傳回該亂數陣列。
    * API： randomN(n, a, b)
    * 範例： randomN(3, 5, 10) => [6, 9, 7]
2. 請從 npm 當中尋找一個可以將檔案壓縮成 zip 的套件，並使用這個套件來寫出一個壓縮程式。(您可以從 npm 官網中輸入 zip 關鍵字查詢出這類套件)
    * 範例： $node zip somedir
    * 結果會將 somedir 資料夾整個壓縮成 somedir.zip
