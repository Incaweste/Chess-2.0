#include "GameManagement.h"

GameManagement& GameManagement::GetGameManagement() noexcept
{
	static GameManagement gameManagement;
	return gameManagement;	
}

void GameManagement::StartGame()
{
	_chessboard = std::make_shared<BaseChessboard>(8);
	_activePlayer = std::make_unique<Player>(_chessboard, true);
	_inactivePlayer = std::make_unique<Player>(_chessboard, false);

	_activePlayer->ActivateSelection();
}

Vector2 GameManagement::GetSizeOfActiveBlocks() const noexcept
{
	Vector2 sizeOfActiveBlocks{0, 0};
	sizeOfActiveBlocks += _chessboard->GetSizeInChars();
	return sizeOfActiveBlocks;
}

std::vector<TextBlock> GameManagement::GetActiveBlocks() const
{
	std::vector<TextBlock> textBlocks;
	textBlocks.reserve(1);
	textBlocks.emplace_back(_chessboard->BuildTextBlock({}, {}));
	return textBlocks;
}

void GameManagement::Update()
{
	while (_currentGameState != GameState::OFF)
	{
		Blinkable::UpdateAll();

		Console::ResetCaret();
		if(Console::DoesThisFitInConsole(GetSizeOfActiveBlocks()))
			Console::DrawTextBlocks(GetActiveBlocks());
		else
			Console::DrawWstring(L"Not enough space for GUI");

		Console::RefreshConsoleAfterCaret();

		ProcessKeyboardInput(Console::GetKeyboardInput());
	}
}

void GameManagement::ProcessKeyboardInput(std::span<const KEY_EVENT_RECORD> keyboardEvents)
{

	for (const auto& event : keyboardEvents)
	{
		if (!event.bKeyDown)
			continue;
		for (DWORD i = 0; i < event.wRepeatCount; ++i)
		{
			if (event.dwControlKeyState == LEFT_CTRL_PRESSED)
			{
				if (event.wVirtualKeyCode == VK_F5)
					Console::RefreshConsole();
			}
			else
			{
				if (event.wVirtualKeyCode == VK_RETURN)
				{

					if (_currentGameState == GameState::PIECE_SELECTION)
					{
						if (_chessboard->CalculateAllowedMoves())
							_currentGameState = GameState::PATH_SELECTION;
					}
				}
				else if (event.wVirtualKeyCode == VK_ESCAPE)
				{
					if (_currentGameState == GameState::PATH_SELECTION)
					{
						_currentGameState = GameState::PIECE_SELECTION;
						_chessboard->ClearAllowedMoves();
					}
					else
						_currentGameState = GameState::OFF;
				}
				else if (VK_LEFT <= event.wVirtualKeyCode && event.wVirtualKeyCode <= VK_DOWN)
				{
					const Utilits::DeltaMove direction = static_cast<Utilits::DeltaMove>(event.wVirtualKeyCode);
					if (_currentGameState == GameState::PIECE_SELECTION)
						_activePlayer->GoToNextSelection(direction);
					else if (_currentGameState == GameState::PATH_SELECTION)
						_chessboard->SetNextMarkedCell(direction);
				}
			}
		}
	}
}