#pragma once
#include<list>
#include<memory>

class StringsModel
{
public:
	struct IsTuned{};
	void onEvent(IsTuned);
	class Listener
	{
	public:
		virtual ~Listener() = default;

		virtual void onEvent(IsTuned) {};
	};
	struct AutoOn {};
	struct AutoOff {};
	void onEvent(AutoOn);
	void onEvent(AutoOff);
	
	class Informator
	{
	public:
		virtual ~Informator() = default;

		virtual float getStringFrequency() = 0;
		virtual int getNearestString(float freq) = 0;
	};
	float getStringFrequency();
	Informator* getInformator();

	StringsModel(Informator*);
	virtual ~StringsModel() = default;

	void addListener(Listener*);
	void deleteListener(Listener*);

	struct FreqChange { float freq; };
	struct StringChange { int string; };
	void onEvent(FreqChange);
	void onEvent(StringChange);

	int getCurrentStringId() const;

private:
	class ChangeStringStrategi
	{
	public:
		ChangeStringStrategi(StringsModel* model) :
			m_model(model) {};
		virtual ~ChangeStringStrategi() = default;

		virtual void onEvent(FreqChange) {};
		virtual void onEvent(StringChange) {};
	protected:
		StringsModel* m_model;
	};
	class ChangeStringOnFreqChange : public ChangeStringStrategi
	{
	public:
		ChangeStringOnFreqChange(StringsModel* model) :
			ChangeStringStrategi(model) {};
		virtual ~ChangeStringOnFreqChange() = default;
		void onEvent(FreqChange) override;
	};
	class ChangeStringOnButton : public ChangeStringStrategi
	{
	public:
		ChangeStringOnButton(StringsModel* model) :
			ChangeStringStrategi(model) {};
		virtual ~ChangeStringOnButton() = default;
		void onEvent(StringChange) override;
	};

	friend class ChangeStringOnButton;
	friend class ChangeStringOnFreqChange;

	int m_current_string{ 1 };

	std::unique_ptr<ChangeStringStrategi>	m_strategi;

	Informator* m_informator{ nullptr };

	std::list<Listener*> m_listeners;
};