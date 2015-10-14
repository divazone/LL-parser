**LL parser說明文件**

此LL paser目前只能LL(1)的部分，並且是以課本上的範例來進行測試

code.txt內容為需要解析的語句
grammer.txt內容為文法內容
output.txt為輸出的parse tree

main.cpp部分為讀取grammer和code部分和執行下列fuction

ffset.cpp為first follow set的定義
可印出經由first set 和follow set之後的內容

ll.cpp為使用Depth-first Search 演算法來進行語法的分析
將語句放入Stack和Queue中並印出每個步驟方便來驗證是否有每步語法分析是否有問題
還可印出整個LL table result方便檢視整個檢視步驟
最後可印出整棵parsing tree

terminals.cpp為檢查語句內容
並且可以印出那些字為Terminals哪些字為Non-Terminals和那些為Nullable


production.cpp為定義grammer放置的容器，定義出LHS和RHS
為 LHS (left-hand side) -> RHS (right-hand side)

demo圖
![solarized LLparser](https://github.com/divazone/LL-parser/blob/master/pic.png)
