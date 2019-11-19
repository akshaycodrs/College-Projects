#include<bits/stdc++.h>
using namespace std;

void printMessage(string message,bool printTop = true,bool printBottom = true){
    if(printTop){
        cout<<"+---------------------------------+"<<endl;
        cout<<"|";
    }
    else{
        cout<<"|";
    }

    bool front = true;
    for(int i = message.length();i<33;i++){
        if(front){
            message = " " + message;
        }
        else{
            message = message + " ";
        }
        front = !front;
    }

    cout<<message;

    if(printBottom){
        cout<<"|"<<endl;
        cout<<"+---------------------------------+"<<endl;
    }
   else{
        cout<<"|"<<endl;
    }
}

void drawHangman(int guesscount){
        if(guesscount >= 1){
            printMessage("|",false,false);
        }
        else{
            printMessage("",false,false);
        }
        if(guesscount >= 2){
            printMessage("|",false,false);
        }
        else{
            printMessage("",false,false);
        }
        if(guesscount >= 3){
            printMessage("O",false,false);
        }
        else{
            printMessage("",false,false);
        }
        if(guesscount == 4){
            printMessage("/  ",false,false);
        }
        if(guesscount == 5){
            printMessage("/|  ",false,false);
        }
        if(guesscount >= 6){
            printMessage("/|\\",false,false);
        }
        else{
            printMessage("",false,false);
        }   
        if(guesscount >= 7){
            printMessage("|",false,false);
        }
        else{
            printMessage("",false,false);
        }   
        if(guesscount == 8){
            printMessage("/ ",false,false);
        }
        if(guesscount >= 9){
            printMessage("/ \\ ",false,false);
        }
        else{
            printMessage("",false,false);
        }      
}

void printLetters(string input,char from,char to){
    string s;
    for(char i=from;i<=to;i++){
        if(input.find(i) == string::npos){
            s = s + i;
            s = s + " ";
        }
        else{
            s = s + "  ";
        }
    }
    printMessage(s,false,false);
}

void printAvailabeLetters(string letters){
    printMessage("Available Letters");
    printLetters(letters,'A','M');
    printLetters(letters,'N','Z');
}

bool printWordAndCheckWin(string word, string guess){
    bool won =  true;
    string s;
    for(int i=0;i<word.length();i++){
        if(guess.find(word[i]) == string::npos){
            won = false;
            s+="_ ";
        }
        else{
            s+=word[i];
            s+=" ";
        }
    }
    printMessage(s,false);
    return won;
}

string loadRandomWord(string path){
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if(reader.is_open()){
        while(std::getline(reader,word))
            v.push_back(word);

        int randomLine = rand() % v.size();

        word = v.at(randomLine);
        reader.close();
    }
    return word;
}

int triesLeft(string word, string guessed){
    int error = 0;
    for(int i=0;i<guessed.length();i++){
        if(word.find(guessed[i]) == string :: npos){
            error++;
        }
    }
    return error;
}

int main(){
    srand(time(0));
    string guesses ;
    string wordToGuess;
    wordToGuess = loadRandomWord("words.txt");
    int tries = 0;
    bool win = false;

    do
    {
        system("cls");
        printMessage("Hangman Game");
        drawHangman(tries);
        printAvailabeLetters(guesses);
        printMessage("Guess the word");
        win = printWordAndCheckWin(wordToGuess,guesses);

        if(win)
        break;

        char x;
        cout<<" > ";
        cin>>x;
        if(guesses.find(x) == string :: npos){
            guesses += x;
        }

        tries = triesLeft(wordToGuess,guesses);
    } while (tries<10);

    if(win) printMessage("YOU WON");
    else printMessage("YOU LOST");
    system("pause");
    getchar();

    return 0;
}