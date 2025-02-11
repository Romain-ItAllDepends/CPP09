/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgobet <rgobet@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:49:36 by rgobet            #+#    #+#             */
/*   Updated: 2025/01/11 14:46:03 by rgobet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template< typename C, typename M >
M PmergeMe::sortPerPair(C &pair, M &maxi)
{
	int size = pair.size();
	M mini;

	for (std::size_t i = 0; i < maxi.size() - 1; i += 2)
		pair.push_back(std::make_pair(std::max(maxi[i], maxi[i + 1]), std::min(maxi[i], maxi[i + 1])));
	if (mini.empty() == false && *std::max_element(mini.begin(), mini.end()) < maxi.back() && maxi.size() % 2 == 1)
		pair.push_back(std::make_pair(std::max(pair.back().second, maxi.back()), -1));
	else if (maxi.size() % 2 == 1)
		pair.push_back(std::make_pair(-1, maxi.back()));
	maxi.clear();
	for (std::size_t i = size; i < pair.size(); i++)
	{
		if (pair.size() - size % 2 == 1 && i == pair.size())
			continue ;
		if (pair[i].first != -1)
			maxi.push_back(pair[i].first);
		if (pair[i].second != -1)
			mini.push_back(pair[i].second);
	}
	if (maxi.size() > 1)
		maxi = this->sortPerPair(pair, maxi);
	this->sortAndMerge(maxi, mini);
	return maxi;
}

template< typename M >
M PmergeMe::suitJacobsthal(M &mini)
{
	M jacob(2, 2);
	std::size_t tmp = 2;
	std::size_t const n = mini.size();

	for (std::size_t i = 2 ; i < n && tmp <= n ; i++)
	{
		tmp = jacob[i - 1] + 2 * jacob[i - 2];
		jacob.push_back(tmp);
	}
	return jacob;
}

template< typename M >
void PmergeMe::setupSections(M &split, M &mini)
{
	std::size_t count = 0;
	int j;
	M tmp;

	for (std::size_t i = 0; i < mini.size() && i < 4; i += 2)
	{
		if (mini.size() > i + 1)
			tmp.push_back(mini[i + 1]);
		tmp.push_back(mini[i]);
		count += 2;
	}
	for (std::size_t n = 2 ; n < split.size() && mini.size() > 4
		&& mini.size() != tmp.size() ; n++)
	{
		if (mini.size() - 1 >= count + split[n])
			j = count + split[n] - 1;
		else
			j = mini.size() - 1;
		for (std::size_t i = j ; i >= count ; i--)
			tmp.push_back(mini[i]);
		count += split[n];
	}
	mini = tmp;
}

template< typename M >
std::size_t PmergeMe::binarySearch(M container, int target)
{
	int left = 0, right = container.size() - 1, mid = 0;

	while (left <= right)
	{
		mid = (left + right) / 2;
		if (container[mid] == target)
			return mid;
		if (container[mid] < target)
			left = mid + 1;
		else if (container[mid] > target)
			right = mid - 1;
	}
	return left;
}

template< typename M >
M PmergeMe::sortAndMerge(M &maxi, M &mini)
{
	M split;

	if (mini.size() == 1)
	{
		maxi.insert(maxi.begin(), mini[0]);
		return maxi;
	}
	if (mini.empty() == true)
		throw std::string("Error: An empty container has been detected!");
	split = suitJacobsthal(mini);
	if (maxi.size() != 1)
		setupSections(split, mini);
	for (std::size_t i = 0 ; i < mini.size() ; i++)
		maxi.insert(maxi.begin() += binarySearch(maxi, mini[i]), mini[i]);
	return maxi;
}

template< typename M >
void PmergeMe::display(M &c, bool e)
{
	for (std::size_t i = 0 ; i < c.size() ; i++)
	{
		if (i == c.size() - 1 && e == false)
			PRINTG c[i] END
		else if (e == false)
			PRINTG c[i] N ", " N NC;
		if (i == c.size() - 1 && e == true)
			PRINTRB c[i] END
		else if (e == true)
			PRINTRB c[i] N ", " N NC;
	}
}
