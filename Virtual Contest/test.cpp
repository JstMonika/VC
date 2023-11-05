//* return the number of the string T in the string S.
ll KMP(string S, string T) {
    string tmp = T + "@" + S;
    
    vec<int> count(tmp.size(), -1);
    
    int ret = 0;
    for (int i = 1; i < tmp.size(); i++) {
        int len = count[i-1];
        
        while (len != -1) {
            if (tmp[i] == tmp[len+1])
                break;
            else len = count[len];
        }
        
        if (tmp[i] == tmp[len+1]) count[i] = len + 1;
        else count[i] = -1;
            
        if (count[i]+1 == T.size()) ret++;
    }
    
    return ret;
}