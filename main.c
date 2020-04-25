#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 9

int a = 0;
int didEat = 0;
int changed = 0;
char board[SIZE][SIZE];

void newGame(){
    FILE *_boardFile = fopen("board.txt", "w+");
    for (int i = 0; i < 8; ++i) {
        board[i][0] = 56-i;
    }
    for (int i = 0; i < 8; ++i) {
        board[8][i+1] = i+65;
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; ++j) {
            if(board[i][j] != 'w' && j != 0 && i != 8 && i != 1 && i != 2 && i != 5 && i != 6 && board[i][j] != 'b'){
                fprintf(_boardFile, "_");
            }else{
                if(i == 8 && j == 0){
                    fprintf(_boardFile, "+");
                }else if ((i == 1 || i == 2) && j != 0){
                    fprintf(_boardFile, "w");
                }else if ((i == 5 || i == 6) && j != 0){
                    fprintf(_boardFile, "b");
                }
                else{
                    fprintf(_boardFile, "%c" ,board[i][j]);
                }
            }
        }
        fprintf(_boardFile, "\n");
    }
    fclose(_boardFile);
}
char getChar(int x1, int x2){
    char a;
    x1 = 8-x1;
    FILE *file = fopen("board.txt", "r+");
    fseek(file, (x1 * 11) + x2, SEEK_SET);
    a = fgetc(file);
    fclose(file);
    return a;
}
void writeChar(int x1, int x2, char a){
    FILE *file = fopen("board.txt", "r+");
    fseek(file, ((8-x1) * 11) + x2, SEEK_SET);
    fprintf(file, "%c" ,a);
    fclose(file);
}
int findAroundDama(char letter1, char loc_1, char thisLetter){//c5BwW
    char oppoLetter, upperOppoLetter;
    int i;
    int x = 0;
    if(thisLetter == 'B' || thisLetter == 'W'){
        if(thisLetter == 'B'){
            oppoLetter = 'w';
            upperOppoLetter = 'W';
        }
        else if(thisLetter == 'W'){
            oppoLetter = 'b';
            upperOppoLetter = 'B';
        }
        i = letter1 - 'a' + 2; //left to right
        while (1){
            if((i == 8 && getChar(loc_1 - '0', 8) == '_') || i > 8){
                x = 0;
                break;
            }
            if(getChar(loc_1 - '0', i) == '_'){
                i++;
            }
            else if (getChar(loc_1 - '0', i) == oppoLetter || getChar(loc_1 - '0', i) == upperOppoLetter){
                if(getChar(loc_1 - '0', i + 1) == '_'){
                    return 1;
                }else{
                    x = 0;
                    break;
                }
            }else if(getChar(loc_1 - '0', i) == thisLetter || getChar(loc_1 - '0', i) == thisLetter + 32){
                x = 0;
                break;
            }
            else{
                x = 0;
            }
        }
        i = letter1 - 'a'; //right to left
        while (1){
            if(i == 1 && getChar(loc_1 - '0', 1) == '_'){
                x = 0;
                break;
            }
            if(getChar(loc_1 - '0', i) == '_'){
                i--;
            } else if (getChar(loc_1 - '0', i) == oppoLetter || getChar(loc_1 - '0', i) == upperOppoLetter){
                if(getChar(loc_1 - '0', i - 1) == '_'){
                    return 1;
                    break;
                } else{
                    x = 0;
                    break;
                }
            }else if(getChar(loc_1 - '0', i) == thisLetter || getChar(loc_1 - '0', i) == thisLetter + 32){
                x = 0;break;
            }
            else{
                x = 0;
                break;
            }
        }
        i = loc_1 - '0' + 1; //bottom to top
        while (1){
            if(i == 8 && getChar(i, letter1 - 'a' + 1) == '_'){
                x = 0;
                break;
            }
            if(getChar(i, letter1 - 'a' + 1) == '_'){
                i++;
            }else if (getChar(i, letter1 - 'a' + 1) == oppoLetter || getChar(i, letter1 - 'a' + 1) == upperOppoLetter){
                if(getChar(i + 1, letter1 - 'a' + 1) == '_'){
                    return 1;
                } else{
                    x = 0;
                    break;
                }
            }else if(getChar(i, letter1 - 'a' + 1) == thisLetter || getChar(i, letter1 - 'a' + 1) == thisLetter + 32){
                x = 0;break;
            }else{
                x = 0;
                break;
            }
        }
        i = loc_1 - '0' - 1; //top to bottom
        while (1){
            if(i == 1 && getChar(i, letter1 - 'a' + 1) == '_'){
                x = 0;
                break;
            }
            if(getChar(i, letter1 - 'a' + 1) == '_'){
                i--;
            } else if (getChar(i, letter1 - 'a' + 1) == oppoLetter || getChar(i, letter1 - 'a' + 1) == upperOppoLetter){
                if(getChar(i - 1, letter1 - 'a' + 1) == '_'){
                    return 1;
                } else{
                    x = 0;
                    break;
                }
            }else if(getChar(i, letter1 - 'a' + 1) == thisLetter || getChar(i, letter1 - 'a' + 1) == thisLetter + 32){
                x = 0;break;
            }else{
                x = 0;
                break;
            }
        }
    }
    return x;
}
int findAround(int position, int letterIndice, char thisLetter, char oppositeLetter){
    int i = 0;
    if(getChar(position,letterIndice) == thisLetter){
        if(getChar(position, letterIndice + 1) == oppositeLetter && getChar(position,letterIndice + 2) == '_'){
            a = 1; i = 1;
            //printf("%c%d%c%d\n", letterIndice + 'a'- 1, position, letterIndice + 1 + 'a', position);
        }
        if(getChar(position,letterIndice - 1) == oppositeLetter && getChar(position, letterIndice - 2) == '_'){
            a = 1; i = 1;
            //printf("%c%d%c%d\n", letterIndice + 'a'- 1, position, letterIndice - 3 + 'a', position);
        }
        if(getChar(position+1, letterIndice) == oppositeLetter && getChar(position+2, letterIndice) == '_'  && thisLetter == 'b'){
            a = 1; i = 1;
            //printf("%c%d%c%d\n", letterIndice + 'a'- 1, position, letterIndice + 'a'- 1, position + 2);
        }
        if(getChar(position-1,letterIndice) == oppositeLetter && getChar(position-2, letterIndice) == '_' && thisLetter == 'w'){
            a = 1; i = 1;
            //printf("%c%d%c%d\n", letterIndice + 'a'- 1, position, letterIndice + 'a'- 1, position-2);
        }
    }
    return i;
}
void findAllStones(char keyWordLetter){
    a = 0;
//    if(keyWordLetter == 'b'){
//        printf("List of BLACK player's moves to eat a stone");
//        printf("\n-------------------------------------------\n");
//    }
//    if(keyWordLetter == 'w'){
//        printf("List of WHITE player's moves to eat a stone");
//        printf("\n-------------------------------------------\n");
//    }
    for (int i = 8; i > 0; i--) {
        for (int j = 1; j < 9; j++) {
            //printf("%d-%d\t", i,j);
            if(getChar(i,j) == keyWordLetter){
                if(keyWordLetter == 'b'){
                    //printf("%d, %d. ", i, j);
                    findAround(i,j, 'b' ,'w');
                }else if(keyWordLetter == 'w'){
                    findAround(i,j, 'w' ,'b');
                }
            }
        }
    }
    //printf("\n-------------------------------------------");
}
int move(char letter1, char loc_1, char letter2, char loc_2){
    changed = 0;
    int firstLetterIndice = letter1 - 'a' + 1;
    int location_1 = loc_1 - '0';
    int secondLetterIndice = letter2 - 'a' + 1;
    int location_2 = loc_2 - '0';
    char firstLetter = getChar(location_1, firstLetterIndice);
    char secondLetter = getChar(location_2, secondLetterIndice);

    if(getChar(0,0) == '+'){
        if(secondLetter == '_' && location_1 + 1 == location_2 && firstLetter == 'b' && a != 1){ //e6c6
            writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            didEat = 0;changed = 1;
        }else if(secondLetter == '_' && location_1 == location_2 && firstLetter != secondLetter && firstLetter == 'b' && abs(secondLetterIndice - firstLetterIndice) <= 1 && a != 1){
            writeChar(location_2, secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            didEat = 0;changed = 1;
        }else if((getChar(location_2,secondLetterIndice - 1) == 'w' || getChar(location_2,secondLetterIndice - 1) == 'W') && getChar(location_1, secondLetterIndice) == '_' && getChar(location_1,firstLetterIndice) == 'b'){
            writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            writeChar(location_2,firstLetterIndice+1,'_');
            didEat = 1;changed = 1;
        }else if((getChar(location_2,secondLetterIndice + 1) == 'w' || getChar(location_2,secondLetterIndice + 1) == 'W') && getChar(location_1, secondLetterIndice) == '_' && getChar(location_1,firstLetterIndice) == 'b'){
            writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            writeChar(location_2,firstLetterIndice-1,'_');
            didEat = 1;changed = 1;
        }else if(getChar(location_1, firstLetterIndice) == 'b' && (getChar(location_1 + 1,secondLetterIndice) == 'w' || getChar(location_1 + 1,secondLetterIndice) == 'W') && getChar(location_2, secondLetterIndice) == '_'){
            writeChar(location_1, firstLetterIndice, '_');
            writeChar(location_1+1, firstLetterIndice, '_');
            writeChar(location_2, firstLetterIndice, 'b');
            didEat = 1;changed = 1;
        }else {
            printf("\nPlease enter a valid location to move\n");
            changed = 0;
            didEat = 0;
        }
        if(getChar(8,secondLetterIndice) == 'b'){
            writeChar(8, secondLetterIndice, 'B');
        }
    }
    else if(getChar(0,0) == '-'){
        if((secondLetter == '_' && location_1 == location_2 + 1 && firstLetter == 'w')){//h5h3
            writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            didEat = 0;changed = 1;
        }else if(secondLetter == '_' && location_1 == location_2 && firstLetter != secondLetter && firstLetter == 'w' && abs(secondLetterIndice - firstLetterIndice) <= 1){
            writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            didEat = 0;changed = 1;
        }else if((getChar(location_2,secondLetterIndice-1) == 'b' || getChar(location_2,secondLetterIndice-1) == 'B') && getChar(location_1,secondLetterIndice) == '_' && getChar(location_1,firstLetterIndice) == 'w'){
            printf("burda");
            writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            writeChar(location_2,secondLetterIndice-1,'_');
            didEat = 1;changed = 1;
        }else if((getChar(location_2,secondLetterIndice + 1) == 'b' || getChar(location_2,secondLetterIndice + 1) == 'B') && getChar(location_1, secondLetterIndice) == '_' && getChar(location_1,firstLetterIndice) == 'w'){
            printf("surda");writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_1, firstLetterIndice, '_');
            writeChar(location_2,firstLetterIndice-1,'_');
            didEat = 1;changed = 1;
        }else if(getChar(location_1,firstLetterIndice) == 'w' && getChar(location_2,secondLetterIndice) == '_' && (getChar(location_2 + 1,firstLetterIndice) == 'b' || getChar(location_2 + 1,firstLetterIndice) == 'B')){
            printf("yog burda");writeChar(location_2,secondLetterIndice, firstLetter);
            writeChar(location_2 + 1, firstLetterIndice, '_');
            writeChar(location_1,firstLetterIndice,'_');//c3c1
            didEat = 1;changed = 1;
        }else {
            printf("\nPlease enter a valid location to move\n");
            changed = 0;
            didEat = 0;
        }
        if(getChar(1,secondLetterIndice) == 'w'){
            writeChar(1, secondLetterIndice, 'W');
        }
    }
    return didEat;
}
void changeTurn(){
    if(getChar(0,0) == '-'){
        writeChar(0,0,'+');
    }else if(getChar(0,0) == '+'){
        writeChar(0,0,'-');
    }
}
int isBetweenClear(char startLetter, int startPos, char targetLetter, int targetPos, char oppositeLetter){//a1a4
    int x = 0;
    int countOfOpposite = 0;
    if(startLetter == targetLetter){
        for (int i = 1; i < abs(startPos - targetPos); i++) { //1,2
            if(startPos < targetPos){
                if(getChar(startPos + i, targetLetter - 'a' + 1) == '_'){
                    x = 1;
                }else if(getChar(startPos + i, targetLetter - 'a' + 1) == oppositeLetter || getChar(startPos + i, targetLetter - 'a' + 1) == oppositeLetter - 32){
                    countOfOpposite++;
                    if(countOfOpposite > 1){
                        x = 0;
                        break;
                    }
                }else{
                    x = 0;
                    break;
                }
            }else if(targetPos < startPos){
                if(getChar(targetPos + i, startLetter - 'a' + 1) == '_'){
                    x = 1;
                }else if(getChar(targetPos + i, startLetter - 'a' + 1) == oppositeLetter || getChar(targetPos + i, startLetter - 'a' + 1) == oppositeLetter - 32){
                    countOfOpposite++;
                    if(countOfOpposite > 1){
                        x = 0;
                        break;
                    }
                }else{
                    x = 0;
                    break;
                }
            }
        }
    }
    else if(targetPos == startPos){
        for (int i = 1; i < abs((targetLetter - 'a' + 1) - (startLetter - 'a' + 1)); i++) {
            if((targetLetter - 'a' + 1) <= (startLetter - 'a' + 1)){
                if(getChar(startPos, targetLetter - 'a' + 1 + i) == '_'){
                    x = 1;
                }else if(getChar(startPos, targetLetter - 'a' + 1 + i) == oppositeLetter || getChar(startPos, targetLetter - 'a' + 1 + i) == oppositeLetter - 32){
                    countOfOpposite++;
                    if(countOfOpposite > 1){
                        x = 0;
                        break;
                    }
                }else{
                    x = 0;
                    break;
                }
            }else if((targetLetter - 'a' + 1) > (startLetter - 'a' + 1)){
                if(getChar(startPos, startLetter - 'a' + 1 + i) == '_'){
                    x = 1;
                }else if(getChar(startPos, startLetter - 'a' + 1 + i) == oppositeLetter || getChar(startPos, startLetter - 'a' + 1 + i) == oppositeLetter - 32){
                    countOfOpposite++;
                    if(countOfOpposite > 1){
                        x = 0;
                        break;
                    }
                }else{
                    x = 0;
                    break;
                }
            }
        }
    }

    if(countOfOpposite == 1){
        x = 2;
    }

    return x;
}
void changeBetween(char letter1, char pos1, char letter2, char pos2){//d2d5
    int horizontalSpace = abs((letter1 - 'a' + 1) - (letter2 - 'a' + 1));
    int verticalSpace = abs((pos2 - '0') - (pos1 - '0'));

    if(letter1 == letter2){
        for (int i = ((pos1 - '0') > (pos2 - '0') ? 1 : 0); i <= ((pos1 - '0') > (pos2 - '0') ? verticalSpace : verticalSpace - 1); ++i) {
            writeChar(((pos1 - '0') >= (pos2-'0') ? (pos2-'0') : (pos1 - '0')) + i, letter1 - 'a' + 1, '_');
        }
    }else if(pos1 == pos2){
        for (int i = (letter1 - 'a' + 1) > (letter2 - 'a' + 1) ? 1 : 0; i <= ((letter1 - 'a' + 1) > (letter2 - 'a' + 1) ? horizontalSpace : horizontalSpace - 1); ++i) {
            writeChar(pos1 - '0', ((letter1 - 'a' + 1) >= (letter2 - 'a' + 1) ? (letter2 - 'a' + 1) : (letter1 - 'a' + 1)) + i, '_');
        }
    }
}
int moveDama(char letter1, char loc_1, char letter2, char loc_2){
    int firstLetterIndice = letter1 - 'a' + 1;
    int location_1 = loc_1 - '0';
    int secondLetterIndice = letter2 - 'a' + 1;
    int location_2 = loc_2 - '0';
    char upperOppo;
    char opposite;
    char thisLetter = getChar(location_1, firstLetterIndice);

    if(thisLetter == 'b' || thisLetter == 'B'){
        opposite = 'w';
        upperOppo = 'W';
    }else if(thisLetter == 'w' || thisLetter == 'W'){
        opposite = 'b';
        upperOppo = 'B';
    }

    if((loc_1 - '0' != 0) && (isBetweenClear(letter1, location_1, letter2, location_2, opposite) == 1 || isBetweenClear(letter1, location_1, letter2, location_2, upperOppo) == 1 )){
        changeBetween(letter1,loc_1,letter2,loc_2);
        writeChar(location_2, secondLetterIndice, thisLetter);
        didEat = 0; changed = 1;
    }
    else if ((loc_1 - '0' != 0) && (isBetweenClear(letter1, location_1, letter2, location_2, opposite) == 2 || isBetweenClear(letter1, location_1, letter2, location_2, upperOppo) == 2)){
        changeBetween(letter1,loc_1,letter2,loc_2);
        writeChar(location_2, secondLetterIndice, thisLetter);
        didEat = 1; changed = 1;
    }
    else if ((loc_1 - '0' != 0) && abs(location_2-location_1) == 1 && getChar(location_2, letter2 - 'a' + 1) == '_'){
        changeBetween(letter1,loc_1,letter2,loc_2);
        writeChar(location_2, secondLetterIndice, thisLetter);
        didEat = 0; changed = 1;
    } else if ((loc_1 - '0' != 0) && abs(firstLetterIndice - secondLetterIndice) == 1 && getChar(location_2, letter2 - 'a' + 1) == '_'){
        changeBetween(letter1,loc_1,letter2,loc_2);
        writeChar(location_2, secondLetterIndice, thisLetter);
        if(isBetweenClear(letter1, location_1, letter2, location_2, opposite) == 2 || isBetweenClear(letter1, location_1, letter2, location_2, upperOppo) == 2){
            didEat = 1; changed = 1;
        }
    }

    return didEat;
}
int main(){
    char blackTurn[] = "It's BLACK's turn-->";
    char whiteTurn[] = "It's WHITE's turn-->";
    char input1, input2, input3, input4;
    char keyWordLetter, upperKeyLetter;
    char oppositeLetter, upperOppoLetter;
    char s;

    while(1==1){
            if(getChar(0,0) == '-'){
                keyWordLetter = 'w';
                upperKeyLetter = 'W';
                oppositeLetter = 'b';
                findAllStones(keyWordLetter);
                printf("\n%s", whiteTurn);
            }
            else {
                keyWordLetter = 'b';
                upperKeyLetter = 'B';
                oppositeLetter = 'w';
                findAllStones(keyWordLetter);
                printf("\n%s", blackTurn);
            }
            int x;
            scanf("%c%c%c%c%c", &input1, &input2, &input3, &input4, &s); //d5e5
            if(getChar(input2 - '0', input1 - 'a' + 1) == upperKeyLetter){
                x = moveDama(input1,input2,input3,input4);
            } else {
                x = move(input1, input2, input3, input4);
            }
            while(x == 1){
                input1 = input3;
                input2 = input4;
                while (getChar(input2 - '0', input1 - 'a' + 1) == keyWordLetter ? findAround(input4 - '0', input3 - 'a' + 1, keyWordLetter, oppositeLetter) : findAroundDama(input1, input2, upperKeyLetter)){
                    printf("%c%c-->", input1, input2);
                    scanf("%c%c%c", &input3, &input4, &s);
                    if(findAroundDama(input1, input2, upperKeyLetter) && getChar(input2 - '0', input1 - 'a' + 1) == upperKeyLetter){
                        moveDama(input1, input2, input3, input4);
                    }
                    else if(findAround(input2 - '0', input1 - 'a' + 1, keyWordLetter, oppositeLetter) || findAround(input2 - '0', input1 - 'a' + 1, keyWordLetter, upperOppoLetter)){
                        move(input1, input2, input3, input4);
                    }
                    input1 = input3;
                    input2 = input4;
                }
                if(changed == 1){
                    break;
                }
            }
            char thisLetter = getChar(input4 - '0', input3 - 'a' + 1);
            if(didEat == 1){
                if(changed == 1){
                    if(findAround(input4 - '0', input3 - 'a' + 1, thisLetter, oppositeLetter) || findAroundDama(input3, input4, thisLetter)){
                        printf("You can continue to eat stone(s) with this stone");
                    } else
                        changeTurn();
                }
            } else if(didEat == 0){
                if(changed == 1){
                    changeTurn();
                }
            }
            if(input1 == 'e' && input2 == 'x' && input3 == 'i' && input4 == 't'){
                break;
            }
        }
        return 0;
}