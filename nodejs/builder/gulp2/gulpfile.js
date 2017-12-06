var gulp = require('gulp');
var md2html = require('./md2html')

gulp.task('default', ['md']);

gulp.task('md', function() {
  // place code for your default task here
  gulp.src('md/*.md')
  .pipe(md2html())
  .pipe(gulp.dest('html'));  
});
