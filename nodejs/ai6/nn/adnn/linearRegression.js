var Tensor = require('adnn/tensor')
var ad = require('adnn/ad')
var nn = require('adnn/nn')
var opt = require('adnn/opt')

// Linear regression test

// Build training data by putting random inputs through a known function
var trueFunc = nn.linear(5, 5);
ad.value(trueFunc.weights).fromArray(
	[[1, 0, 0, 0, 0],
	 [0, 2, 0, 0, 0],
	 [0, 0, 3, 0, 0],
	 [0, 0, 0, 4, 0],
	 [0, 0, 0, 0, 5]]
);

ad.value(trueFunc.biases).fromArray([5, 4, 3, 2, 1]);
var data = [];
var N = 10000;
for (var i = 0; i < N; i++) {
	var x = new Tensor([5]).fillRandom();
	var y = trueFunc.eval(x);
	data.push({
		input: x,
		output: y
	});
}

// Train
var trainFunc = nn.linear(5, 5);
console.time('training');
opt.nnTrain(trainFunc, data, opt.regressionLoss, {
	iterations: 10000,
	batchSize: 1,
	method: opt.sgd({ stepSize: 1, stepSizeDecay: 0.999 }), // test:pass
	// method: opt.adagrad({ stepSize: 1 }), // test:pass
	// method: opt.rmsprop(), // test:pass
	// method: opt.adam(), // test:pass
	verbose: false
});
console.timeEnd('training');
console.log(ad.value(trainFunc.weights).toArray());
console.log(ad.value(trainFunc.biases).toArray());

