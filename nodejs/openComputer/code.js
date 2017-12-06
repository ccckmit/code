var c = require("./ccc");

var code = function(line, opTable) {
  this.parseR = function(str) {
    var rmatch = /R(\d+)/.exec(str);
    if (rmatch == null)
      return NaN;
    return parseInt(rmatch[1]);
  }

  this.toString = function() {
    return c.format("%s %s %s %s %s %s %s", c.hex(this.address, 4), 
      c.fill(' ',this.label,8), c.fill(' ',this.op.name, 8), 
      c.fill(' ',this.args, 16), this.op.type, c.hex(this.op.id,2), this.obj);
  }
  
  var labCmd = /^((\w+):)?\s*([^;]*)/;
  var parts  = labCmd.exec(line);           // ���ΥX�аO�P�R�O
  var tokens = parts[3].trim().split(/[ ,\t\r]+/); // �N�R�O���Φ��򥻳椸
  var opName = tokens[0];                   // ���X���O�W��
  
  this.label = c.nonull(parts[2]);          // ���X�аO (\w+)
  this.args  = tokens.slice(1);             // ���X�ѼƳ���
  this.op    = opTable[opName];
  this.obj   = ""; 
}

module.exports = code;
