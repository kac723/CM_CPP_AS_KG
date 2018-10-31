# CM_CPP_AS_KG
Assignment project for CM and CPP by Axel Simon and Kacper Grajcar

Step to do in Computational Method:
1) Correct analytical solution : Done
2) Test  explicit Upwind schemes and lax schemes and compare with analytical : Done
2.5) Implement norms + test : Done
3) Implement algorithm to solve linear sytem of equation (Thomas algorithm): Done
4) Implicit upwind schemes : Done
5) Test and compare with analytical solution : Done
6) Implicit FTCS schemes : Done
7) Test and compare with analytical solution : Done

Step to do in C++:
1) Create Class : Done
2) Add exceptions handling
3) Add printing methods
4) Add more comments to code
5) Improve Matrix class
6) clean up #include in all files

comande gnuplot:
plot 'output1.txt' u 1:2 w l t 't = 0', 'output1.txt' u 1:3 w l t 't = 0.1', 'output1.txt' u 1:4 w l t 't = 0.2', 'output1.txt' u 1:5 w l t 't = 0.3', 'output1.txt' u 1:6 w l t 't = 0.4','output1.txt' u 1:7 w l t 't = 0.5'
plot 'analyticalOutput.txt' u 1:2 w l t 't=0','analyticalOutput.txt' u 1:3 w l t 't=0.1','analyticalOutput.txt' u 1:4 w l t 't=0.2','analyticalOutput.txt' u 1:5 w l t 't=0.3', 'analyticalOutput.txt' u 1:6 w l t 't=0.4', 'analyticalOutput.txt' u 1:7 w l t 't=0.5'