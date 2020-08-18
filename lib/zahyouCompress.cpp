// 重複削除とソート
template<class T>
void deleteJufukuAndSort(vector<T> &vect)
{
	sort(vect.begin(), vect.end());
	vect.erase(unique(vect.begin(), vect.end()), vect.end());
}

// ベクターを値とインデックスのマップに圧縮
template <class T> 
map<T, int> compressVectorToMap(vector<T> vect)
{
	int cmpIdx = 0;
	map<T, int> idxTblMap;
	
	// 重複削除
	sort(vect.begin(), vect.end());
	vect.erase(unique(vect.begin(), vect.end()), vect.end());
	
	// 昇順にインデックスを割り当て
	for (auto one : vect) {
		idxTblMap[one] = cmpIdx;
		cmpIdx++;
	}

	return idxTblMap;
}

// ベクターをインデックスのマップに変換
template <class T>
map<T, int> vectorToIdxMap(const vector<T> &vect)
{
	int cmpIdx = 0;
	map<T, int> idxTblMap;

	// 並びはそのままでインデックスを割り当て
	for (auto one : vect) {
		idxTblMap[one] = cmpIdx;
		cmpIdx++;
	}

	return idxTblMap;
}
