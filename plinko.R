library("ggplot2")
make_board <- function() {
  # create the left half of a plinko board...
  x = c(-.5,0,rep(c(-.5,0),times=5),-.5)
  y = c(0,0,1:11)
  df = data.frame(x,y)
  # create right half
  x2 = 9-x
  y2 = y
  df2 = data.frame(x2,y2)
  # add data for dots for "pegs" in the board
  evens=1:8
  odds=seq(.5,9,by=1)
  xvals = evens
  yvals = rep(0,length(evens))
  for (y in 1:10) {
    if (y%%2==0) {
      xvals=c(xvals,evens)
      yvals=c(yvals,rep(y,length(evens)))
    }
    else {
      xvals=c(xvals,odds)
      yvals=c(yvals,rep(y,length(odds)))
    }
  }
  board = ggplot() + geom_polygon(data=df,aes(x,y),fill="yellow") + 
    geom_polygon(data=df2,aes(x2,y2),fill="yellow") + 
    geom_point(data=data.frame(xvals,yvals),aes(xvals,yvals),size=.5) +
    coord_equal() +
    scale_y_continuous(limits=c(0,11),breaks=0:10) +
    scale_x_continuous(breaks=0:9,limits=c(-.5,9.5)) +
    theme(panel.grid.major = element_blank(), panel.grid.minor = element_blank())
  return(board)
}

board = make_board()
board

# 1) The path that the disk took
simulate_plinko <- function(slot){
  slot = slot - 0.5
  path = c(rep(0,10),slot)
  for(level in 10:1){
    fallRight = sample(c(-1,1),size=1, replace=T)
    if(slot == 0){
      slot = slot + 0.5
    }
    else if(slot == 9){
      slot = slot - 0.5
    }
    else{
      slot = slot + (fallRight * 0.5)
    }
    path[level] = slot
  }
  return(path)
}

# 2A) 5 random slots (including their paths)
pathTaken <- function(count, start, board){
  start = rep(start, each = ceiling(count/length(start)), len = count)
  for(diskColor in 1:count){
    pointdata = numeric(0)
    if(start[diskColor] == 0){
      start[diskColor] =sample(1:9,1,replace=T) 
    }
    pointdata <- data.frame(
      xname <- simulate_plinko(start[diskColor]),
      ypos <- 0:10
    )
    board = board + 
      geom_path(data = pointdata, mapping = aes_string(x = xname, y = ypos)) + 
      geom_point(data = pointdata, mapping = aes_string(x = xname, y = ypos), color=diskColor, size = 5)
  }
  board
}
pathTaken(5, 0,board)

# 2B) Histogram
histogram <-function(num, slot){
  result = matrix(0, ncol = 9, nrow = 1)
  for(i in 1:num){
    temp = simulate_plinko(slot)[1]
    result[temp+0.5] = result[temp+0.5] + 1
  }
  barplot(result, main="average outcome", xlab="slots", names.arg=c(1:9), ylim=c(0,ceiling(max(result)/5)*5))
  return(result)
}
histogram(50, 1)

# 3) Average Mean Prize
meanPrice = function(num, slot){
  prize = matrix(data = c(100,500,1000,0,10000,0,1000,500,100), ncol = 9, nrow = 1)
  return(sum(histogram(num, slot) * prize)/num)
}
meanPrice(50, 5)

#4) Maximize your expected winnings
maxWin = function(num, times){
  wins = matrix(0, ncol = 9, nrow = 1)
  winnings = matrix(0, ncol = 9, nrow = 1)
  while(max(wins)<times){
    for(slot in 1:9){
      winnings[slot] = meanPrice(num, slot)
    }
    wins[which.max(winnings)] = wins[which.max(winnings)] + 1
  }
  return(which.max(wins))
}
maxWin(50, 5)
