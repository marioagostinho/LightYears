#include <framework/Actor.h>

#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "player/Player.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFramerateText("Frame rate:"),
		mPlayerHealthBar(),
		mPlayerLifeIcon("SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"),
		mPlayerLifeText(""),
		mPlayerScoreIcon("SpaceShooterRedux/PNG/Power-ups/star_gold.png"),
		mPlayerScoreText(""),
		mHealthyHealthBarColor(128, 255, 128, 255),
		mCriticialHealthBarColor(255, 0, 0, 255),
		mCriticalThreshold(0.3f),
		mWidgetSpacing(10.f),
		mWinLoseText("You Win!"),
		mFinalScoreText("0"),
		mRestartButton("Restart"),
		mQuitButton("Quit"),
		mWindowSize()
	{
		mFramerateText.SetTextSize(20.f);
		mPlayerLifeText.SetTextSize(20.f);
		mPlayerScoreText.SetTextSize(20.f);

		SetFinalHUDVisibility(false);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateText = "Frame Rate: " + std::to_string(frameRate);
		mFramerateText.SetString(frameRateText);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mWindowSize = windowRef.getSize();

		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);

		mWinLoseText.NativeDraw(windowRef);
		mFinalScoreText.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}

	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		return mRestartButton.HandleEvent(event)
			|| mQuitButton.HandleEvent(event)
			|| HUD::HandleEvent(event);
	}

	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mPlayerHealthBar.SetWidgetLocation({15.f, windowSize.y - 50.f});

		sf::Vector2f nextWidgetPos = mPlayerHealthBar.GetWidgetLocation();
		nextWidgetPos += sf::Vector2f{ mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeIcon.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeText.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeText.GetBound().width + mWidgetSpacing * 4.f, -2.f };
		mPlayerScoreIcon.SetWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerScoreIcon.GetBound().width + mWidgetSpacing, 0.f };
		mPlayerScoreText.SetWidgetLocation(nextWidgetPos);

		RefreshHealthBar();
		ConnectPlayerStatus();

		mWinLoseText.SetTextSize(40);
		mFinalScoreText.SetTextSize(40.f);

		mRestartButton.SetWidgetLocation({ windowSize.x / 2.f - mRestartButton.GetBound().width / 2.f, windowSize.y / 2.f});
		mQuitButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 50.f });

		mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
	}

	void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);

		if (currentHealth / maxHealth < mCriticalThreshold)
		{
			mPlayerHealthBar.SetForegroundColor(mCriticialHealthBarColor);
		}
		else
		{
			mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
		}
	}

	void GameplayHUD::PlayerLifeCountUpdated(int amt)
	{
		mPlayerLifeText.SetString(std::to_string(amt));
	}

	void GameplayHUD::PlayerScoreUpdated(int newScore)
	{
		mPlayerScoreText.SetString(std::to_string(newScore));
	}

	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* Actor)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();

		if (player && !player->GetCurrentSpaceship().expired())
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);

			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp();
			healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
			PlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
			mPlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::ConnectPlayerStatus()
	{
		Player* player = PlayerManager::Get().GetPlayer();

		if (player)
		{
			int lifeCount = player->GetLifeCount();
			mPlayerLifeText.SetString(std::to_string(lifeCount));
			player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

			int playerScore = player->GetScore();
			mPlayerScoreText.SetString(std::to_string(playerScore));
			player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
		}
	}

	void GameplayHUD::SetHUDVisibility(bool visibility)
	{
		mFramerateText.SetVisibility(visibility);
		mPlayerHealthBar.SetVisibility(visibility);
		mPlayerLifeIcon.SetVisibility(visibility);
		mPlayerLifeText.SetVisibility(visibility);
		mPlayerScoreIcon.SetVisibility(visibility);
		mPlayerScoreText.SetVisibility(visibility);
	}

	void GameplayHUD::SetFinalHUDVisibility(bool visibility)
	{
		mWinLoseText.SetVisibility(visibility);
		mFinalScoreText.SetVisibility(visibility);
		mRestartButton.SetVisibility(visibility);
		mQuitButton.SetVisibility(visibility);
	}

	void GameplayHUD::RestartButtonClicked()
	{
		onRestartBtnClicked.Broadcast();
	}

	void GameplayHUD::QuitButtonClicked()
	{
		onQuitBtnClicked.Broadcast();
	}

	void GameplayHUD::GameFinished(bool playerWon)
	{
		mWinLoseText.SetString(playerWon ? "You Win" : "You Lose");
		mWinLoseText.SetWidgetLocation({ mWindowSize.x / 2.f - mWinLoseText.GetBound().width / 2.f, 100.f });

		int score = PlayerManager::Get().GetPlayer()->GetScore();
		mFinalScoreText.SetString("Score: " + std::to_string(score));
		mFinalScoreText.SetWidgetLocation({ mWindowSize.x / 2.f - mFinalScoreText.GetBound().width / 2.f, 200.f });

		SetHUDVisibility(false);
		SetFinalHUDVisibility(true);
	}
}