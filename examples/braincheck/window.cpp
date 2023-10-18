#include "window.hpp"
#include <random>
#include <thread>

void Window::onCreate() {
  // Load font with bigger size for the X's and O's
  auto const filename{abcg::Application::getAssetsPath() +
                      "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 72.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError{"Cannot load font file"};
  }

  restartGame();
}

void Window::onPaintUI() {
  // Get size of application's window
  auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
  auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};

  // "Tic-Tac-Toe" window
  {
    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    auto const flags{ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse};
    ImGui::Begin("Brain-Check", nullptr, flags);

    // Menu
    {
      bool restartSelected{};
      if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Game")) {
          ImGui::MenuItem("Restart", nullptr, &restartSelected);
          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }
      if (restartSelected) {
        restartGame();
      }
    }

    // Static text showing current turn or win/draw messages
    {
      std::string text;
      switch (m_gameState) {
      case GameState::Play:
        text = fmt::format("Sua pontuacao = {} Numero de tentativas = {}", pontosJog, cont/2);
        break;
      case GameState::Win:
        text = "Voce venceu!";
        break;
      case GameState::Lose:
        text = "Voce perdeu garotinho!";
        break;
      }
      // Center text
      ImGui::SetCursorPosX(
          (appWindowWidth - ImGui::CalcTextSize(text.c_str()).x) / 2);
      ImGui::Text("%s", text.c_str());
      ImGui::Spacing();
    }

    ImGui::Spacing();
    
    // Game board
    {
      auto const gridHeight{appWindowHeight - 22 - 60 - (m_N * 10) - 60};
      auto const buttonHeight{gridHeight / m_N};

      // Use custom font
      ImGui::PushFont(m_font);
      if (ImGui::BeginTable("Game board", m_N)) {
        for (auto i : iter::range(m_N)) {
          ImGui::TableNextRow();
          for (auto j : iter::range(m_N)) {
            ImGui::TableSetColumnIndex(j);
            auto const offset{i * m_N + j};

            // Get current character
            auto ch{m_board.at(offset)};

            if (ch == 0) {
              ch = ' ';
            }

            // Button text is ch followed by an ID in the format ##ij
            auto buttonText{fmt::format("{}##{}{}", ch, i, j)};
            if (ImGui::Button(buttonText.c_str(), ImVec2(-1, buttonHeight))) {
                if (m_gameState == GameState::Play && ch == ' ') {
                  cont ++;
                  if(!verifyPair(cont)){
                    fst = offset;
                    m_board.at(fst) = m_board_cards.at(fst);
                  }

                  if(verifyPair(cont)){
                    snd = offset;
                    m_board.at(snd) = m_board_cards.at(snd);
                  }

                //Todo segundo click
                if(verifyPair(cont)){
                  //no momento do segundo clique ele verifica se os dois cards sao iguais
                  if(m_board_cards.at(snd)==m_board_cards.at(fst)){
                    //PontosJog[m_XsTurn] = PontosJog[m_XsTurn] + 1;
                    pontosJog ++;
                  } else if(m_board_cards.at(snd)!=m_board_cards.at(fst)) {
                    //esconde os campos caso tenha errado
                    m_board.at(fst) = 0;
                    m_board.at(snd) = 0;
                  }
                    checkEndCondition();
                }   
              }
            }
          }
          ImGui::Spacing();
        }
        ImGui::EndTable();
      }
      ImGui::PopFont();
    }

    ImGui::Spacing();

    // "Restart game" button
    {
      if (ImGui::Button("Restart game", ImVec2(-1, 50))) {
        restartGame();
      }
    }

    ImGui::End();
  }
}

void Window::checkEndCondition() {
  if (pontosJog == 8){
    m_gameState = GameState::Win;
    return;
  }
  //execedeu 10 tentativas
  if (cont/2  > 10){
    m_gameState = GameState::Lose;
    return;
  }

  return;
}

void Window::shuffleBoard() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Embaralhe as cartas no vetor m_board_cards
    std::shuffle(m_board_cards.begin(), m_board_cards.end(), gen);
}

void Window::restartGame() {
  //board oculto do jogo (tentar randomizar dps)
  m_board_cards = {'@','!','$','?',
                   '@','-','%','&',
                   '&','+','?','!',
                   '%','+','-','$'};

  shuffleBoard();
  
  m_board.fill('\0');
  cont = 0; //cont dos cliques
  pontosJog = 0; //pontos por acerto de par
  m_gameState = GameState::Play;
}

bool Window::verifyPair(int cont) {
  
  if(cont%2 == 0){
    return true;
  }
    else{
      return false;
    }
}