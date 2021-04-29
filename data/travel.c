

char* CalcRoutePath(char *path, int line){
    int len;
    strcpy(path,"data/routes/route");
    len = strlen(path);
    path[len] = line + '0';
    path[len+1] = '\0';
    strcat(path, ".out");
    return path;
}

char* CalcStationPath(char *path, int station){
    int len;
    strcpy(path,"data/stations/_");
    len = strlen(path);
    path[len] = station/10 + '0';
    path[len+1] = station % 10 + '\0';
    path[len+2] = '\0';
    return path;
}

void ReadLineInfo(Lines *l, int line){
    char path[32];
    FILE *fp;
    path = CalcRoutePath(path, line);
    fp = fopen(path, "rb");
    fread(l, sizeof(Lines), 1, fp);
    fclose(fp);
    fp = NULL;
}

void DisplayTraces(int line, int start, int end){
    int ids = -1, ide = -1, i, reverse = 0;
    FILE *fp;
    Lines l;
    Station cur, pre;
    char path[32];
    ReadLineInfo(&l, line);
    for(i = 1; i <= l.n; i++){
        if(l.station_numbers[i] == start){
            ids = i;
            if(ide != -1)reverse = 1;
        }
        if(l.station_numbers[i] == end){
            ide = i;
        }
    }
    DrawStart(start);
    DrawEnd(end);
    if(reverse == 1){
        i = end;
        end = start;
        start = i;
    }
    for(i = start; i <= end; i++){
        fp = fopen(CalcStationPath(path, l.station_numbers[i]), "rb");
        fread(&cur, sizeof(cur), 1, fp);
        fclose(fp);
        fp = NULL;
        if(i == start)continue;
        Line3(cur.x, cur.y, pre.x, pre.y, 12, BLUE);
        pre = cur;
    }
    for(i = start + 1; i < end; i++){
        fp = fopen(CalcStationPath(path, l.station_numbers[i]), "rb");
        fread(&cur, sizeof(cur), 1, fp);
        Circlefill(cur.x, cur.y, 9, RED);
        fclose(fp);
        fp = NULL;
    }
}