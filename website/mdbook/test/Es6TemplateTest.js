var reply = { _id: '111reply1', user: 'ddd', msg: 'aaaaaaa', time: '20170305'}
var postId = '111'
var user = 'ccc'

var replyOp = (reply.user === user) ? `<i class="fa fa-times" title="delete" onclick="SMS.deleteReply('${postId}','${reply._id}')"></i>` : ``

var replyHtml = `
<div id="reply${reply._id}" class="reply">
<div contenteditable="true" class="replyMsg" onkeyup="SMS.replyEditKeyup('${postId}', '${reply._id} this.innerText)">${reply.msg}</div>
<div style="float:right">
 <i class="fa fa-user" title="Author"></i>
 <a href="/view/${reply.user}">${reply.user}</a>
 ${replyOp}
 <i class="fa fa-clock-o" title="${reply.date}"></i>
 </div>
</div>
`

console.log(replyHtml)


