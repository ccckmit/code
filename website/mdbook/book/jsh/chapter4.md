# 第 4 章 - 函數


## 簡介

當您學會了 if, while 這些控制結構之後，基本上就可以寫出所有的程式了，但是卻沒辦法寫出好的程式。

因為、一個好的程式，必需要有很好的結構。

換句話說、好的程式可以讓我們隨時呼叫其中的功能，讓我們可以不用一再重寫類似的程式碼，就可以透過呼叫其他程式來完成我們想要的工作。

因此我們需要函數！

有了函數，程式就能擁有好的結構，程式就能被模組化，然後輕易的被呼叫，這就是本章的主題：《函數》的用途了！

讓我們先看一個函數的例子，那就是取大值 max(a,b) ，這個函數會傳回 a, b 兩者當中較大的那一個數值。

## 取大值

檔案：max.js

```
function max(a,b) {
  if (a>b)
    return a;
  else
    return b;
}

m = max(9,5);
console.log("max(9,5)="+m);
```

執行結果：

```
nqu-192-168-61-142:code mac020$ node max.js
max(9,5)=9
```

在此必須說明一點，函數呼叫時，參數的傳遞與名稱無關，而是與參數的位置有關。

舉例而言，上面我們用 max(9,5) 呼叫 max 函數，此時 a, b 分別會帶入 a=9, b=5 的值進去，因此判斷式會得到 if (9>5) return 9; 於是會傳回 9.

但是如果我們用下列的呼叫方式，那麼就會得到 z=7。

```
x=3; y=7;
z = max(x,y); // 此時 x 會代入 a, y 會代入 b 於是得到 max(x,y) = max(3,7) = 7
```

假如呼叫時有 a, b 等變數，也不會因為名稱相同而代入，而是按照位置填入，舉例而言，在以下程式中，

```
a=8; b=2;
c = max(b,a); // 此時 b=2 會代入參數 a, 而 a=8 會代入參數 b 於是得到 max(b,a) = max(2,8) = 8
```

總而言之，函數是根據呼叫時的位置代入的，而非根據名字。

## 計算總和

您可以在函數裡面使用前面幾章所學到的任何控制結構，像是 if, while, for, switch, 陣列，變數等等。

檔案： fsum.js

```

function sum(n) {
  var s=0;
  for (i=1; i<=n; i++) {
	s = s+i;
  }
  return s;
}

sum10 = sum(10);
console.log("1+...+10="+sum10);

```

執行結果：

```
nqu-192-168-61-142:code mac020$ node fsum.js
1+...+10=55
```

## 質數測試

檔案： prime.js

```
function isPrime(n) {
  for (var i=2; i<n; i++) {
    if (n%i === 0)
      return false;
  }
  return true;
}

console.log("isPrime(33)="+isPrime(33));
console.log("isPrime(17)="+isPrime(17));

for (var p=1; p<=100; p++) {
  if (isPrime(p))
    console.log("isPrime("+p+")");
}

```

執行結果

```
nqu-192-168-61-142:code mac020$ node prime.js
isPrime(33)=false
isPrime(17)=true
isPrime(1)
isPrime(2)
isPrime(3)
isPrime(5)
isPrime(7)
isPrime(11)
isPrime(13)
isPrime(17)
isPrime(19)
isPrime(23)
isPrime(29)
isPrime(31)
isPrime(37)
isPrime(41)
isPrime(43)
isPrime(47)
isPrime(53)
isPrime(59)
isPrime(61)
isPrime(67)
isPrime(71)
isPrime(73)
isPrime(79)
isPrime(83)
isPrime(89)
isPrime(97)
nqu-192-168-61-142:code mac020$ 

```

## 匿名函數

在 JavaScript 當中，函數的宣告方法大致有兩種，第一種的宣告方法就和一般程式語言 (C/C++, Python, Java) 等差不多，是採用 f(a,b,c...) 這種方式宣告的，但是必須在前面加上 function 這個關鍵字。

在以下範例中， sub(a,b) 就是採用這種方式宣告的一個範例。

檔案：function.js

```javascript
// 第一種寫法，直接宣告函數
function sub(a,b) {         
  return a-b;
}

// 第二種寫法，將匿名函數指定給變數。
var add = function(a,b) {     
  return a+b;
}
console.log("add(3,5)=", add(3,5), " sub(7,2)=", sub(7,2));
```

執行結果：

```
D:\js\code>node function.js
add(3,5)= 8  sub(7,2)= 5
```

但是、在 JavaScript 當中，還有一種比較特別函數宣告方式，是在宣告了一個「匿名函數」之後，再把這個函數「塞給」一個變數。就像上述的 `var add = function(a,b) ...` 的做法，這樣我們就可以用 add(3,5) 這樣的方式去呼叫該函數了。

必須注意的是，函數應該先定義之後再使用，否則有可能會發生《該函數不存在》的問題。

舉例而言，如果你將上述程式

檔案： addUndef.js

```javascript
console.log("add(3,5)=", add(3,5));

var add = function(a,b) {     
  return a+b;
}
```

執行時就會發現有如下的錯誤，這就是因為 add 函數在還沒定義時就被呼叫的原因。

```
D:\jsbook>node addUndef.js
D:\jsbook\addUndef.js:1
(function (exports, require, module, __filename, __dirname) { console.log("add(3
,5)=", add(3,5));

       ^

TypeError: add is not a function
    at Object.<anonymous> (D:\jsbook\addUndef.js:1:88)
    at Module._compile (module.js:425:26)
    at Object.Module._extensions..js (module.js:432:10)
    at Module.load (module.js:356:32)
    at Function.Module._load (module.js:313:12)
    at Function.Module.runMain (module.js:457:10)
    at startup (node.js:138:18)
    at node.js:974:3
```


## 參數的傳遞

有些人說，javascript 傳遞參數都是採用傳值的方式，這種說法雖然不能說錯，但必須注意一件事。

對於基礎型態，像是數值、布林值等等，是採用傳值的方式，也就是複製一份之後再傳給函數，但是對於像陣列、物件、字串等等，雖然也是複製一份傳給函數，但是複製的卻是其指標，因此對於這些復合結構的物件而言，說白了就是採用傳參照的方式。

參考： <http://heyyou.logdown.com/posts/145054>

基本型態的參數，如果你在函數內進行修改，並不會影響外部的那個對應變數，但是如果是物件型態的參數，由於是採用傳參照的方式，這代表兩者其實是參照到同一個物件內容，所以對應的外部變數也會被修改。

以下的範例展示了這兩類參數被修改後的結果：

檔案： modify.js

```javascript
function modify(num, array) {
  num = num + 1;
  array[0] = array[0] + 1;	
}

var n=3, a=[3,2,1];

modify(n, a);

console.log("n=", n, " a=", a);
```

執行結果：

```
$ node modify
n= 3  a= [ 4, 2, 1 ]
```

## 函數型態的參數

在上面的 add 範例中，我們將「函數」塞給一個變數，而且還可以直接把該變數當作函數來呼叫。

那麼、我們能不能將函數當作參數來傳遞呢？ 

關於這點、當然是可以的，以下是一個將「函數當作參數」的範例。

檔案： fptr.js

```javascript
function sub(a,b) {         
  return a-b;
}

function f5(f, a) {
  return f(a, 5);
}

console.log("sub(8,5)="+sub(8, 5));
console.log("f5(sub,8)="+f5(sub,8));
```

執行結果

```
D:\Dropbox\Public\web\js\code>node fptr
sub(8,5)=3
f5(sub,8)=3
```

您可以看到，函數 `f5(f, a)` 的參數 f，其實又是一個函數，因為我們在 f(a,5) 當中把 f 當作函數來呼叫。

所以、當我們呼叫 f5(sub, 8) 的時候，該函數會傳回 3，因為當我們將 f5(sub, 8) 內容中的 f 取代為 sub，而 a 取代為 8 時，就會發現 return 語句的 f(a,5) 其實就是 sub(8,5)，所以當然就會傳回 3 囉！

## 呼叫不特定函數

既然可以將函數當成參數傳入，那麼我們就可以設計一個如下的 run 函數，該函數在執行完待呼叫函數 f 之後，再把執行結果印出來。

檔案： run.js

```
function run(f, x) {
  var fx = f(x);
  console.log("f(x)="+fx);
}

run(Math.sin, Math.PI/4);
```

執行結果

```
D:\Dropbox\cccweb\db\js\code>node run.js
f(x)=0.7071067811865475
```

## 套用函數在陣列中的每個元素上

透過將函數傳入的方式，我們也可以設計出處理陣列中每個元素的高階函數，舉例而言，以下的 each 函數就是一個範例。

檔案： each.js

```
function each(a, f) {
  for (var i in a) {
    f(a[i]);
  }
}

each([3,4,5,6], console.log);

function sinPrint(x) {
  console.log("sin(%d)=%d", x, Math.sin(x));
}

each([3,4,5,6], sinPrint);
```

執行結果

```
D:\Dropbox\cccweb\db\js\code>node each.js
3
4
5
6
sin(3)=0.1411200080598672
sin(4)=-0.7568024953079282
sin(5)=-0.9589242746631385
sin(6)=-0.27941549819892586
```

我們也可以設計出如下的 map 函數將整個陣列套用函數後轉換成另一個陣列。

檔案： map.js

```
var c = console;

function map(f, a) {
  var ma = [];
  for (var i in a) {
    ma.push(f(a[i]));
  }
  return ma;
}

function square(x) {
  return x*x;
}

c.log("map(x^2, [3, 1, 5, 4, 2])="+map(square, [3,1,5,4,2]));
c.log("map(sin(x), [3, 1, 5, 4, 2])="+map(Math.sin, [3,1,5,4,2]));
```

執行結果

```
D:\Dropbox\cccweb\db\js\code>node map.js
map(x^2, [3, 1, 5, 4, 2])=9,1,25,16,4
map(sin(x), [3, 1, 5, 4, 2])=0.1411200080598672,0.8414709848078965,-0.9589242746
631385,-0.7568024953079282,0.9092974268256817
```

## 回呼 (callback)

既然可以將函數當成參數傳入，那麼我們就可以將某個函數傳入，等到某些動作執行完成之後再呼叫該函數，這種方法就稱為回呼 Callback 。

在 node.js 或網頁中，我們常常需要在輸出入動作完成後進行回呼，或者是在某些適當的時機去執行某些函數，這些都可以採用上述的回呼技術來設計。


### 微分

檔案： df.js

```
function df(f, x) {
  var dx = 0.001;
  var dy = f(x+dx) - f(x);
  return dy/dx;
}

function square(x) {
  return x*x;
}

console.log('df(x^2,2)='+df(square, 2));
console.log('df(x^2,2)='+df(function(x){ return x*x; }, 2));
console.log('df(sin(x/4),pi/4)='+df(Math.sin, 3.14159/4));
```

執行結果

```
D:\Dropbox\cccweb\db\js\code>node df.js
df(x^2,2)=4.000999999999699
df(x^2,2)=4.000999999999699
df(sin(x/4),pi/4)=0.7067535793015001
```

### 積分

檔案： integral.js

```
function integral(f, a, b) {
  var dx = 0.001;
  var area = 0.0;
  for (var x=a; x<b; x=x+dx) {
    area = area + f(x)*dx;
  }
  return area;
}

function square(x) {
  return x*x;
}

console.log('integral(x^2,0,1)='+integral(square,0,1));
console.log('integral(sin(x),0,pi)='+integral(Math.sin,0,3.14159));
```

執行結果

```
D:\Dropbox\cccweb\db\js\code>node integral.js
integral(x^2,0,1)=0.33283350000000095
integral(sin(x),0,pi)=1.9999999540411524
```

## 箭頭函數

以下的 square2 採用箭頭函數進行回呼！

```js
var numbers = [1, 4, 9]
var square1 = numbers.map(function (num) {
  return num * num
})

var square2 = numbers.map((num) => num * num)

console.log('square1=%j', square1)
console.log('square2=%j', square2)
```

## 亂數: 取 (a,b) 範圍間的亂數 (浮點數版 -- rand)

```
$ node
> function rand(a,b) { return a+Math.random*(b-a); }
undefined
> rand(1,10)
NaN
> function rand(a,b) { return a+Math.random()*(b-a); }
undefined
> rand(1,10)
9.309291471494362
> rand(1,10)
3.008262322982773
> rand(1,10)
3.473059037467465
```


## 取 (a,b) 範圍間的亂數 (整數版 -- randInt)

```
$ node
> function randInt(a,b) { return Math.floor(a+Math.random()*(b-a)); }
undefined
> randInt(1,10)
4
> randInt(1,10)
5
> 
> randInt(1,10)
7
> randInt(1,10)
2
> randInt(1,10)
2
> randInt(1,10)
8
> randInt(1,10)
3
> randInt(1,10)
1
>
```

## 從陣列中隨機選擇一個元素 randSelect(a)

```
$ node
> function randSelect(a) { return a[randInt(0,a.length)]; }
undefined
> randSelect([1,7,4])
1
> randSelect([1,7,4])
1
> randSelect([1,7,4])
4
> randSelect([1,7,4])
7
> randSelect([1,7,4])
7
> function randSelect(a) { return a[randInt(0,a.length)]; }
undefined
> randSelect([1,7,4])
4
> randSelect(['a','g','c'])
'a'
> randSelect(['a','g','c'])
'c'
> randSelect(['a','g','c'])
'a'
> randSelect(['a','g','c'])
'g'
> randSelect(['a','g','c'])
'g'
> randSelect(['a','g','c'])
'g'
> randSelect(['dog','cat'])
'cat'
> randSelect(['dog','cat'])
'dog'
> randSelect(['dog','cat'])
'cat'
> randSelect(['dog','cat'])
'cat'
> randSelect(['dog','cat'])
'dog'
> randSelect(['dog','cat'])
'cat'
```

## 習題

關於基本函數呼叫的練習，請看第3章的習題！

請您在已經熟練第3章的基本函數之後，再回來做本章的習題，因為這些習題屬於比較進階的議題，必須有第3章的習題作為基礎。

### 回呼函數實作
1. 請寫一個函數可以傳回陣列的映射值？ 
    * 範例：map(sqrt, [1,4,9])= [1,2,3]
2. 請寫一個函數可以根據過濾函數f只留下符合的內容？ 
    * 範例：filter(odd, [1,3,5,4,8,9])= [1,3,5,9] ，其中 odd 為判斷是否為奇數的函數。
3. 請寫一個函數 df(f,x) 可以做數值微分？ 
    * 範例： df(sin, Pi/4) = 0.707 
4. 請寫一個函數 integral(f, a, b) 可以做數值積分？ 
    * 範例： integral(sin, 0, Pi) = 2

### 遞迴呼叫練習
1. 請用遞迴計算 n! = n*...*2*1 ？ 
    * 範例： factorial(3) = 6
2. 請寫出計算遞迴函數 `f(n) = 2*f(n-1)+f(n-2)` 的函數，其中 f(0)=f(1)=1？ 
    * 範例： `f(2) = 2*1+1 = 3, f(3)=2*3+1=7` 。
3. 請用遞迴計算 power(n,k) = n^k = n*...*n ？ 
    * 範例：power(2,3) = 8
4. 請用遞迴計算 sum(n) = 1+2+...+n  ？ 
    * 範例：sum(10) = 55


除了學習《程式技巧》之外，更重要的是學習《程式的邏輯思維》。

所謂的《演算法》，就是將程式抽象化之後的那種方法，換言之就是《程式的邏輯思維方法》，以下習題可以鍛鍊學習者的《程式邏輯思維能力》，但是相對的會需要比較深度的思考，才能想出這些程式的實作方法。

### 演算法思考練習
1. 求一元二次方程式 ax^2+bx+c=0 的根。 
    * 範例： findroot(1,-4,4) => 2
2. 請寫出 minimal 函數可以找出函數 f 的區域最低點。 
    * 範例： `function f(x) { return x*x-4*x+4; } minimal(f) => x=2, f(2)=0`
3. 請寫出 maximal 函數可以找出函數 f 的區域最高點。 
    * 範例： `function f(x) { return -1*(x*x-4*x+4); } maximal(f) => x=2, f(2)=0`
4. 電腦隨機產生一個 `n*n` 的二維布爾值陣列。用程式檢驗該二維字元陣列中，縱行、橫列及兩條對角線，「O(true)的bingo線」及「X(false)的bingo線」分別有多少條。
    * 輸入 input：一個隨機產生的尺寸 `n*n` 之二維 Boolean 陣列；
    * 輸出 output：兩個 integers 。
5. 請上網查詢何謂《泡沫排序法》，然後寫一個 javascript 程式可以用《泡沫排序法》對陣列進行排序。
    * 範例： bobbleSort([1,7,2,8,5]) => [1,2,5,7,8]