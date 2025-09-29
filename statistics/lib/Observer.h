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
		// m_observers.insert(&observer);
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

		// m_observers.erase(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		for (auto it = m_observers.begin(); it != m_observers.end();)
		{
			if (auto observer = it->lock())
			{
				observer->Update(data);
				++it;
			}
			else
			{
				it = m_observers.erase(it);
			}
		}

		/*for (auto& observer : m_observers)
		{
			observer->Update(data);
		}*/
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	// std::set<ObserverType*> m_observers;

	std::set<std::weak_ptr<ObserverType>, std::owner_less<std::weak_ptr<ObserverType>>> m_observers;
};
