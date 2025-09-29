#pragma once

#include <memory>
#include <set>

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	using ObserverType = IObserver<T>;

	virtual void RegisterObserver(std::shared_ptr<ObserverType> observer) = 0;
	virtual void RemoveObserver(std::shared_ptr<ObserverType> observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual ~IObservable() = default;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(std::shared_ptr<ObserverType> observer) override
	{
		m_observers.insert(observer);
	}

	void RemoveObserver(std::shared_ptr<ObserverType> observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			if (it->lock() == observer)
			{
				m_observers.erase(it);
				break;
			}
		}
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observersCopy = m_observers;

		for (auto& weakObs : observersCopy)
		{
			if (auto obs = weakObs.lock())
			{
				obs->Update(data);
			}
		}
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::set<std::weak_ptr<ObserverType>, std::owner_less<std::weak_ptr<ObserverType>>> m_observers;
};
