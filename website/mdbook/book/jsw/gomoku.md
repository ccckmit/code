# 五子棋

檔案： [gomoku_ui.html](/code/js/gomoku/gomoku_ui.html)

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" rel="stylesheet">
    <style>
body { padding-top: 70px; padding-bottom: 30px; }
#board td   { width:20px; height:20px; color:#336699; }
    </style>
  </head>

  <body>
    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#">五子棋</a>
        </div>
   </nav>

    <div class="container">
      <div class="row">
        <div class="col-md-3"></div>
        <div class="col-md-6">
          <table class="table table-bordered">
            <tbody id="board">
            </tbody>
          </table>
        </div>
      </div>
    </div> <!-- /container -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
    <script>
var turn = 'Ｏ';
var isGameOver = false;
var rows=12, cols=20;

function newBoard() {
  var boardHtml = '';
  for (var x=0; x<rows; x++) {
    var rowHtml = '<tr>';
    for (var y=0; y<cols; y++) {
      rowHtml += '<td id="'+x+'_'+y+'">　</td>';
    }
    rowHtml += '</tr>';
    boardHtml += rowHtml;
  }
  return boardHtml;
}

$(document).ready(function() {
  var boardHtml = newBoard();
  $('#board').html(boardHtml);
  $('#board td').mousedown(function () {
    if (isGameOver) return;
    var id = $(this).attr("id");
    var v = $('#'+id).html();
    if (v==='Ｏ' || v==='Ｘ') return;
    $(this).html(turn);
    turn = (turn==='Ｏ')?'Ｘ':'Ｏ';
  });
});
    </script>
  </body>
</html>

```