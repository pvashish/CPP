#include<iostream>
#include<fstream>
#include<cmath>

class Life {

public:

  uint16_t* life; // +100% if you can do this with just 1 boadrd // life = board (life array)
  uint16_t rows, cols;

public:

  Life(uint32_t rows, uint32_t cols){
    this->rows = rows;
    this->cols = cols;
    life = new uint16_t[rows * cols];
  }

  uint16_t count(uint32_t current_row, uint16_t current_col){ //current_pos = current_row * cols + current_col
    
    uint16_t count = 0;
    uint16_t current_pos = current_row * cols + current_col;
    
    if (current_row == 0){
      if (current_col == 0){
          count = life[current_pos + 1] + life[current_pos + cols] + life[current_pos + cols +1];
      }
      else if (current_col = cols - 1){
            count = life[current_pos - 1] + life[current_pos + cols] + life[current_pos + cols - 1];
      }
      else{
        if (life[current_pos + 1] == 1){
          count = life[current_pos + 1] + life[current_pos - 1] + life[current_pos + cols] + life[current_pos + cols + 1] + life[current_pos + cols - 1];
        }
      }
    }
    
    else if (current_row == rows-1) {
      if (current_col == 0){
          count = life[current_pos + 1] + life[current_pos - cols] + life[current_pos - cols +1];
      }
      else if (current_col = cols - 1){
        if (life[current_pos - 1] == 1){
            count = life[current_pos - 1] + life[current_pos - cols] + life[current_pos - cols - 1];
        }
      }
    }
    
    else if (current_col % cols == 0){
      if(life[current_pos + 1]) {
        count = life[current_pos + 1] + life[current_pos + 1 - cols] + life[current_pos + 1 + cols] + life[current_pos - cols] + life[current_pos + cols];
      }
    }
    
    else if  (current_col % cols == cols - 1){
      if(life[current_pos - 1]){
        count = life[current_pos - 1] + life[current_pos - 1 - cols] + life[current_pos - 1 + cols] + life[current_pos - cols] + life[current_pos + cols];
      }
    }
    
    else{
      count = life[current_pos -1] +  life[current_pos + 1] +  life[current_pos + 1 - cols] + life[current_pos + 1 + cols] + life[current_pos -1 + cols] + life[current_pos -1 - cols]+ life[current_pos + cols] + life[current_pos - cols];
    }

  return count;
  }

  void next(){
    uint16_t* new_life = new uint16_t[rows * cols]; 
    
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j ++){
        if (life[i*cols + j] == 1){
          if (count(i,j) == 2 || count(i,j) == 3){
            new_life[i*cols + j] = 1;
          }
          else{ 
            new_life[i*cols + j] = 0;
          }
        }
        else{
          if (count(i,j) == 3){
            new_life[i*cols + j] = 1;
          }
          else{
              new_life[i*cols + j] = 0;
          }
        }
     }
    }
    delete [] life; 
    life = new_life;
  }

  friend std::ostream &operator<<(std::ostream &obj, Life const &life){
    for (int i = 0; i< life.rows; i++){
      for(int j = 0; j< life.cols; j ++){
        obj<<life.life[i*life.cols+j];
        obj << ' ';
      }
      obj<<'\n';
    }
    obj<<'\n';
    return obj;
  }

};
int main() {
    //https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules
    
    std::ifstream f("my.life.txt");
    uint16_t rows, cols, val;
    uint16_t pos = 0;
    f >> rows>>cols;
    
    Life life(rows, cols);
    while (f>>val){
      life.life[pos] = val;
      pos++;
    }

    for (int i = 0; i< 10; i++) { // 10 = # generations
        std::cout<< life; //printing out a single generation
        life.next();
    }

    Life life2 = life; // make sure copy constructor doesn't crash
    life2 = life; // make sure operator = works
}