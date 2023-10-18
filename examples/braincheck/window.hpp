#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaintUI() override;

private:
  static int const m_N{4}; // Board size is m_N x m_N

  enum class GameState { Play, Win , Lose};
  GameState m_gameState;

  std::array<char, m_N * m_N> m_board{}; 
  std::array<char, m_N * m_N> m_board_cards{}; //16 cards

  ImFont *m_font{};
  
  int cont;
  int pontosJog;
  int fst;
  int snd;

  bool verifyPair(int cont);
  void shuffleBoard();
  void checkEndCondition();
  void restartGame();
};

#endif