

#ifndef UNTITLED11_BRANCH_H
#define UNTITLED11_BRANCH_H

class Branch_Table{
public:
    bool pan[2];
}lastBT[1<<12],newBT[1<<12];



bool BranchJudge(int tmppp){
    if(lastBT[tmppp].pan[0]==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
#endif //UNTITLED11_BRANCH_H
