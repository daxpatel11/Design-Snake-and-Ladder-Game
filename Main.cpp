#include <bits/stdc++.h>

using namespace std;

class Snake{
  
    
    int start;
    int end;
    
      public: 
      
      Snake(int start,int end)
      {
          this->start=start;
          this->end=end;
      }
      int getStart(){
          return start;
      }
      
      int getEnd(){
          return end;
      }
      
};

class Ladder{
  
    
    int start;
    int end;
    
      public: 
      
       Ladder(int start,int end)
      {
          this->start=start;
          this->end=end;
      }
      int getStart(){
          return start;
      }
      
      int getEnd(){
          return end;
      }
      
};

class Player{
    string name;
    // string id;
    public:
    Player (string name){
        this->name = name;
        // this->id = rand(0,10);
    }
     string getName(){
          return name;
      }
      
  
    
};

class SnakeAndLadderBoard{
    int size;
    vector<Snake> snakes;
    vector<Ladder> ladders;
    map<string,int> playerpieces;
    
    public:
    
    SnakeAndLadderBoard(){
        this->size=100;
    }
    int getSize(){
        return size;
    }
    vector<Snake> getSnakes(){
        return snakes;
    }
    void setSnakes(vector<Snake> snakes){
        this->snakes = snakes;
    }
     vector<Ladder> getLadder(){
        return ladders;
    }
    void setLadder(vector<Ladder> ladders){
        this->ladders = ladders;
    }
    
    map<string,int> getplayerpieces(){
        return playerpieces;
    }
    void setPlayerpieces(map<string,int> playerpieces){
        this->playerpieces = playerpieces;
    }
};

class DiceService{
    public :
    int roll(){
       return rand()%6+1;   
    }
    
};

class SnakeAndLadderService {
    SnakeAndLadderBoard snakeandladderboard;
    int intialplayer;
    queue<Player> p;
   
    
    public: 
    bool isCompleted = false;
    SnakeAndLadderService(){
        this->snakeandladderboard = SnakeAndLadderBoard();
    }
    
    void setPlayers(vector<Player> players){
        this->intialplayer = players.size();
        map<string,int> m;
        for(Player player : players){
            p.push(player);
            m[player.getName()] = 0;
        }
        snakeandladderboard.setPlayerpieces(m);
    }
    void setSnakes(vector<Snake> snakes){
        vector<Snake> s ; 
        for(Snake snake : s)
        cout<<snake.getStart()<<" "<<snake.getEnd()<<"\n";
        snakeandladderboard.setSnakes(snakes);
    }
    
    void setLadders(vector<Ladder> ladders){
        snakeandladderboard.setLadder(ladders);
    }
    
    int getnewposition(int newpos){
        int prevpos;
        
        do{
            prevpos=newpos;
            for(Snake snake : snakeandladderboard.getSnakes())
            {
                if(snake.getStart() == newpos)
                {
                    newpos=  snake.getEnd();
                }
            }
             for(Ladder ladder : snakeandladderboard.getLadder())
            {
                if(ladder.getStart() == newpos)
                {
                    newpos=  ladder.getEnd();
                }
            }
        }
        while(newpos!=prevpos);
        
        return newpos;
    }
    
    void movePlayer(Player player,int positions){
        map<string,int> m  =  snakeandladderboard.getplayerpieces();
        int oldpos = m[player.getName()];
        // cout<<oldpos<<"\n";
        int newpos = oldpos+positions;
        // cout<<newpos<<"\n";
        int boardSize = snakeandladderboard.getSize();
        if(newpos>boardSize)
        {
            newpos = oldpos;
        }
        else
        {
            newpos = getnewposition(newpos);
        }
        // cout<<newpos<<"\n";
        m[player.getName()]=newpos;
        // snakeandladderboard.getplayerpieces().insert({player.getName(),newpos});
        // cout<<player.getName()<<" "<<newpos<<"\n";
        snakeandladderboard.setPlayerpieces(m);
        cout<<player.getName() <<" rolled a  "<<positions<<" and moved from "<<oldpos<<" to "<<newpos<<"\n";
        
    }
    
    int getnewvalue(){
        DiceService d1;
        return d1.roll();
    }
    
    bool hasplayerwon(Player player){
        map<string,int> m ;
        m=snakeandladderboard.getplayerpieces();
        int playerpos = m[player.getName()];
        int winpos = snakeandladderboard.getSize();
        return playerpos==winpos;
    }
    
    bool isGameCompleted(){
        int cur_players = p.size();
        return cur_players<intialplayer;
    }
    
    void startGame(){
        int first = 1;
         int count=0;
        while(first ||  p.size()>=2){
            //   cout<<"Game start"<<"\n";
            first=0;
            int totalDicevalue  = getnewvalue();
            cout<<totalDicevalue<<"\n";
            Player current_player = p.front();
            p.pop();
            movePlayer(current_player,totalDicevalue);
           
            if(hasplayerwon(current_player))
            {
                count++;
                cout<<current_player.getName()<<" won " <<count<<" position ################################"<<"\n";
                
                map<string,int> m;
                m.erase(current_player.getName());
                
                
            }
            else
            {
                p.push(current_player);
            }
        }
    }
    
};

int main() {
   int s;
   cin>>s;
   vector<Snake> snakes;
   for(int i=0;i<s;i++)
   {
       int x,y;
       
       cin>>x>>y;
       snakes.push_back(Snake(x,y));
   }
   int l;
   cin>>l;
   vector<Ladder> ladders;
   for(int i=0;i<l;i++)
   {
       int x,y;
       cin>>x>>y;
       ladders.push_back(Ladder(x,y));
   }
   int p;
   cin>>p;
   vector<Player> players;
   for(int i=0;i<p;i++)
   {
       string x;
       cin>>x;
    //   cout<<Player(x).getName()<<"\n";
       players.push_back(Player(x));
   }
   SnakeAndLadderService s1 ;
   s1.setPlayers(players);
   s1.setLadders(ladders);
   s1.setSnakes(snakes);
   s1.startGame();
}
