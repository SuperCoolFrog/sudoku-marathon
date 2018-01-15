# Sudoku Marathon

This is a continuous runnig sudoku game that will allow you to accumulate points indefinitely by solving sudokus.

[Try it out!](http://aws-website-sudoku-marathon-3akgc.s3-website-us-east-1.amazonaws.com/)

# Why a sudoku marathon game?

Originally I was just going to covert a sudoku solver/generator in Reason, but after watching the show Man vs Snake on netflix I decided to create a sudoku marathon game.

# Why Reason?

I was interested in learning Reason and thought this would be a fun project.

# My Reason code is crap?

Please feel free to tear my project apart.  This is used for learning so any advice or improvements are welcomed.

# Sudoku Solver

This is using a ReasonML implementation of the sudoku solver found [here](http://www.emanueleferonato.com/2015/06/23/pure-javascript-sudoku-generatorsolver/)

Right now it is hard coded to work with 9x9

# Build + Watch

```
npm start
```

# Webpack dev server

```
node_modules/.bin/webpack-dev-server
```

# Webpack Build

```
npm run webpack
```
