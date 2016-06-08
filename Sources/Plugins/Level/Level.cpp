#include "Level.hpp"

BEGIN_DERIVED_CLASS(Level, CShPlugin)
	// ...
END_CLASS()

Level::Level(void)
	: CShPlugin(CShIdentifier("Level"))
	, m_loader(new LevelLoader())
	, m_ground(new Ground())
	, m_character(new Character())
{
	
}

/*virtual*/ Level::~Level(void)
{
	
}

void Level::Initialize(void)
{
	
}

void Level::Release(void)
{
	delete m_loader;
	delete m_ground;
	delete m_character;
}

/*virtual*/ void Level::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	m_loader->Load(CShString("test"));
	m_ground->Initialize(*m_loader, 20, 20, 10*1024, 10*1024);
	//TODO : Uncomment when fix released
	//ShInput::AddOnTouchMove(Level::OnTouchMove);
}

/*virtual*/ void Level::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	for(int i = 0; i < s_character.GetCount(); ++i)
	{
		if(s_character[i] == m_character)
		{
			s_character.Remove(i);
			break;
		}
	}
	m_character->Release();
	m_ground->Release();
	m_loader->Release();
}

/*virtual*/ void Level::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	
}

/*virtual*/ void Level::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	
}

/*virtual*/ void Level::OnPreUpdate(void)
{
	static bool first = true;
	if(first)
	{
		first = false;
		m_character->Initialize(CShIdentifier("test"));
		s_character.Add(m_character);
	}
}

/*virtual*/ void Level::OnPostUpdate(float dt)
{
	m_character->Update(dt);
}

/*static*/ void	Level::OnTouchMove(int iTouch, float positionX, float positionY)
{
	for(int i = 0; i < s_character.GetCount(); ++i)
	{
		s_character[i]->OnTouchMove(iTouch, positionX, positionY);
	}
	ShLog(e_log_level_warning, e_log_type_game, 0, "Pos : %f %f", positionX, positionY);
}

/*static*/ void Level::SetReleaseEnabled(bool state)
{
	s_releaseEnabled = state;
}

/*static*/ bool Level::IsRealeseEnabled()
{
	return s_releaseEnabled;
}

/*static*/ bool Level::s_releaseEnabled = true;
/*static*/ CShArray<Character*> Level::s_character;