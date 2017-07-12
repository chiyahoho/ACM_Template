int rand(){return t=t^1;}
int merge(int x,int y){
    if (!x || !y) return x+y;
    if (key[x]>key[y]) swap(x,y);
    if (rand()) lson[x]=merge(lson[x],y);
    else rson[x]=merge(rson[x],y);
    return x;
}