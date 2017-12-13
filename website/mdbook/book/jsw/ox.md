# 專案 -- 井字遊戲

## 第一版：沒有輸贏判斷

檔案： [ox_ui.html](/code/js/ox/ox_ui.html)

程式重點

```

          <table id="ox" class="table table-bordered" style="width:100px">
            <tbody>
              <tr>
                <td id="11">&nbsp;</td>
                <td id="12">&nbsp;</td>
                <td id="13">&nbsp;</td>
              </tr>
              <tr>
                <td id="21">&nbsp;</td>
                <td id="22">&nbsp;</td>
                <td id="23">&nbsp;</td>
              </tr>
              <tr>
                <td id="31">&nbsp;</td>
                <td id="32">&nbsp;</td>
                <td id="33">&nbsp;</td>
              </tr>
            </tbody>
          </table>

...

var turn = 'O';
var isGameOver = false;

$(document).ready(function() {
  console.log('ready()');
  $('#ox td').mousedown(function () {
    if (isGameOver) return;
    var id = $(this).attr("id");
    var v = $('#'+id).html();
    if (v==='O' || v==='X') return;
    $(this).html(turn);
    turn = (turn==='O')?'X':'O';
  });
});
```

## 第二版：有輸贏判斷

檔案： [ox_check.html](/code/js/ox/ox_check.html)

程式重點

```
function get(i,j) {
  return $('#'+i+''+j).html();
}

var x = [[1,1,1], [2,2,2], [3,3,3], [1,2,3], [1,2,3], [1,2,3], [1,2,3], [1,2,3]];
var y = [[1,2,3], [1,2,3], [1,2,3], [1,1,1], [2,2,2], [3,3,3], [1,2,3], [3,2,1]];

function check() {
  for (var i=0; i<x.length; i++) {
    var first = get(x[i][0], y[i][0]);
    for (var j=0; j<3; j++) {
      var cell = get(x[i][j], y[i][j]);
      if (cell === "&nbsp;") break;
      if (cell !== first) break;
      if (j===2)
        return first+"贏了！";
    }
  }  
  return null;
}

var turn = 'O';
var isGameOver = false;

$(document).ready(function() {
  console.log('ready()');
  $('#ox td').mousedown(function () {
    if (isGameOver) return;
    var id = $(this).attr("id");
    var v = $('#'+id).html();
    if (v==='O' || v==='X') return;
    $(this).html(turn);
    turn = (turn==='O')?'X':'O';
    var winMsg = check();
    if (winMsg !== null) {
      alert(winMsg);
      isGameOver = true;
    }
  });
});
```


