#ifndef _AI_CORE_H
#define _AI_CORE_H

#include "chessboard.h"
#include "types.h"
#include <ctime>
#include <cstdlib>
#include <list>
#include <vector>
#include <exception>

#include "boardposition.h"
#include "judgesituation.h"
#include "alphabetapruning.h"

typedef enum{
	ATTACK,
	DEFENCE
} Attack_or_Defence;

typedef struct{
      board_position position;
	  bool hasilive3orabove;
      u32 direction;
      u32 max_length;
	  int score;
}analysis_result;

typedef struct
{
   u32 human_score;
   u32 computer_score;
}human_computer_score;

typedef struct
{
  human_computer_score score;
  board_position position;
}position_score_info;

class AI_core
{
private:
   int advertised_pos[BOARD_SIZE][BOARD_SIZE];
   bool is_copied_already;
   analysis_result alys_rlt;
   s8 human_chess_type;
   s8 computer_chess_type;
   s8 empty_chess_type;
   s8 core_board[BOARD_SIZE][BOARD_SIZE];
   board_position position_suggest;
   std::list<board_position> type1;
   std::list<board_position> type2;
   std::list<board_position> empty_type;
   std::list<board_position>::iterator l_ptr;
   std::vector<std::vector<int>> suggest_position_info;/* 0-horizontal 1-vertical 2-hori_vert 3-anti_hori_vert*/
   std::vector<position_score_info> pos_score_info;
   std::vector<board_position> empty_position_score_results;
   analysis_result analysis_result_position;
private:
   JudgeWin* judgewin_ai;
public:
	AI_core(){
		srand(time(NULL));
		position_suggest.x_pos = BOARD_SIZE/2;
		position_suggest.y_pos = BOARD_SIZE/2;

		this->judgewin_ai = new JudgeWin;
		this->alpha_beta_pruning = new AlphaBetaPruning();

		this->alys_rlt.direction = 0;
		this->alys_rlt.max_length = 0;

		this->human_chess_type = '&';
		this->computer_chess_type = '@';

		for(int i = 0; i < BOARD_SIZE; i++){
			for(int j = 0; j < BOARD_SIZE; j++){
				core_board[i][j] = '+';
				for(int k = 0; k <= BOARD_SIZE/2; k++){
					if(i == k || i == BOARD_SIZE - 1 - k) this->advertised_pos[i][j] = k + 1;
				}
	            for(int k = 0; k <= BOARD_SIZE/2; k++){
	                    if(j == k || j == BOARD_SIZE - 1 - k) this->advertised_pos[i][j] += k;
	            }
			}
		}
		this->is_copied_already = false;
	}      
   ~AI_core(){}
public:
   AI_core(const AI_core&)= delete;
   AI_core& operator=(const AI_core&) = delete;
   AI_core& operator()(const AI_core&) = delete;
public:
   void copy_board(const Chessboard&);
   board_position get_suggest_position();
   bool is_winner(const board_position&,s8);
   s8 get_human_chess_type();
   s8 get_computer_chess_type();
   s8 get_empty_chess_type();
// for test mode
public:
   u32 test_mode(int,board_position,s8);
   void display_advertised_pos() const;
// mode end
private:
   bool is_safe(const board_position&);
   bool is_empty_site(const board_position&);
   void store_chess_info();    
   void destroy_present_chess_info();
   analysis_result get_suggest_analysis_result();
   analysis_result  analysize_guess_position(const board_position&,s8);
   typedef s8 COPY_BOARD[BOARD_SIZE][BOARD_SIZE];
   COPY_BOARD score_board;
   void copy_position(COPY_BOARD&);
   void store_analysis_result(const analysis_result&);
   analysis_result get_present_result();
private:
   analysis_result get_max_score_position(const Chessboard& chessboard,char chesstype);
   analysis_result greedy_analysis(const Chessboard& chessboard,char chesstype);
private:
   s8 board_for_analysis[BOARD_SIZE][BOARD_SIZE];
   board_position position_suggest_of_greedy_analysis;
   std::list<board_position> human_type_of_greedy_analysis;
   std::list<board_position> computer_type_of_greedy_analysis;
   std::list<board_position> empty_type_of_greedy_analysis;
   void copy_chess_for_analysis(COPY_BOARD);
   void destory_chessboard_for_analysis();
   int  chessboard_greedy_analysis(COPY_BOARD,board_position,int);
   void store_chessboard_for_analysis();
   void flush_chessboard_for_analysis();
   void greedy_analysis_empty_position_score(const COPY_BOARD&);
public:
   void analyze_level1(s8);
   void analyze_level2(const Chessboard&, s8);
   void analyze_level3(s8);
private:
   u32 the_position_score_fun1(const COPY_BOARD&,board_position,s8);
   u32 the_position_score_fun2(const COPY_BOARD&,board_position,s8);
   u32 the_position_score_fun3(const COPY_BOARD&,board_position,s8);
   u32 the_position_score_fun4(const COPY_BOARD&,board_position,s8);
   u32 the_position_score_fun5(const COPY_BOARD&,board_position,s8);
   u32 the_position_score_fun6(const COPY_BOARD&,board_position,s8);
   u32 the_position_score_fun7(const COPY_BOARD&,board_position,s8);
   u32 the_position_score_fun8(const COPY_BOARD&,board_position,s8);
   human_computer_score empty_position_score(board_position,const COPY_BOARD&);
   board_position get_pos_of_maxhs();
   board_position get_pos_of_minhs();
   board_position get_pos_of_maxcs();
   board_position get_pos_of_mincs();
   void release_pos_score_info();
   void release_empty_position_score_results();
   void store_empty_position_score(const board_position,const human_computer_score);
   void analysize_empty_position_score();
private:
   Chessmen_info* current_chessboard_chessmeninfo(const Chessboard& chessboard,char chesstype);
   int attack_or_defence(const Chessboard& chessboard,char chesstype,Attack_or_Defence aord,analysis_result& result);

/*the follow features based on alpha-beta pruning*/
private:
   AlphaBetaPruning* alpha_beta_pruning;   
};
#endif//ai_core.h

