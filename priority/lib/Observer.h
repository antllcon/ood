#pragma once

#include <map>
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

	virtual void RegisterObserver(std::shared_ptr<ObserverType> observer, uint64_t priority = 0) = 0;
	virtual void RemoveObserver(std::shared_ptr<ObserverType> observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual ~IObservable() = default;
};

template <class T>
class CObservable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(std::shared_ptr<ObserverType> observer, uint64_t priority = 0) override
	{
		if (m_observerToPriority.find(observer) != m_observerToPriority.end())
		{
			return;
		}

		m_priorityObservers[priority].insert(observer);
		m_observerToPriority[observer] = priority;
	}

	void RemoveObserver(std::shared_ptr<ObserverType> observer) override
	{
		auto it = m_observerToPriority.find(observer);
		if (it == m_observerToPriority.end())
		{
			return;
		}

		auto priority = it->second;
		auto& list = m_priorityObservers[priority];

		for (auto i = list.begin(); i != list.end();)
		{
			if (i->lock() == observer)
			{
				i = list.erase(i);
			}
			else
			{
				++i;
			}
		}

		if (list.empty())
		{
			m_priorityObservers.erase(priority);
		}

		m_observerToPriority.erase(it);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto it = m_priorityObservers.rbegin(); it != m_priorityObservers.rend(); ++it)
		{
			auto observersCopy = it->second;
			for (auto& weakObs : observersCopy)
			{
				if (auto obs = weakObs.lock())
				{
					obs->Update(data);
				}
				else
				{
					// TODO: удалять объект
				}
			}
		}
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::map<uint64_t, std::set<std::weak_ptr<ObserverType>, std::owner_less<std::weak_ptr<ObserverType>>>> m_priorityObservers;
	std::map<std::shared_ptr<ObserverType>, uint64_t> m_observerToPriority;
};
