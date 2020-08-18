/*
 * LookUpTable.c
 *
 *  Created on: Jun 25, 2014
 *      Author: angga
 */
#include "common/look_up_table.h"

const int32_t ACPT2_DUMMY[320]=
{
		1807	,
		1808	,
		1803	,
		1811	,
		1809	,
		1820	,
		1825	,
		1825	,
		1831	,
		1835	,
		1836	,
		1840	,
		1840	,
		1837	,
		1836	,
		1843	,
		1842	,
		1844	,
		1841	,
		1844	,
		1847	,
		1846	,
		1843	,
		1832	,
		1832	,
		1824	,
		1818	,
		1815	,
		1817	,
		1819	,
		1819	,
		1811	,
		1811	,
		1811	,
		1801	,
		1799	,
		1797	,
		1803	,
		1799	,
		1802	,
		1808	,
		1805	,
		1797	,
		1783	,
		1780	,
		1775	,
		1769	,
		1763	,
		1754	,
		1747	,
		1745	,
		1746	,
		1749	,
		1747	,
		1749	,
		1751	,
		1747	,
		1737	,
		1725	,
		1721	,
		1718	,
		1718	,
		1711	,
		1710	,
		1714	,
		1703	,
		1702	,
		1703	,
		1697	,
		1693	,
		1689	,
		1681	,
		1685	,
		1682	,
		1682	,
		1676	,
		1673	,
		1673	,
		1666	,
		1658	,
		1653	,
		1648	,
		1645	,
		1645	,
		1646	,
		1642	,
		1647	,
		1642	,
		1638	,
		1641	,
		1635	,
		1630	,
		1625	,
		1616	,
		1612	,
		1608	,
		1604	,
		1601	,
		1594	,
		1585	,
		1583	,
		1581	,
		1577	,
		1577	,
		1573	,
		1570	,
		1568	,
		1562	,
		1550	,
		1542	,
		1543	,
		1542	,
		1539	,
		1539	,
		1529	,
		1527	,
		1523	,
		1514	,
		1513	,
		1516	,
		1508	,
		1503	,
		1497	,
		1491	,
		1488	,
		1483	,
		1482	,
		1468	,
		1469	,
		1465	,
		1468	,
		1469	,
		1472	,
		1470	,
		1469	,
		1473	,
		1467	,
		1455	,
		1463	,
		1456	,
		1450	,
		1442	,
		1433	,
		1420	,
		1419	,
		1413	,
		1411	,
		1411	,
		1412	,
		1411	,
		1415	,
		1419	,
		1415	,
		1415	,
		1418	,
		1414	,
		1403	,
		1403	,
		1405	,
		1404	,
		1408	,
		1401	,
		1402	,
		1397	,
		1403	,
		1401	,
		1396	,
		1393	,
		1392	,
		1392	,
		1386	,
		1380	,
		1377	,
		1380	,
		1371	,
		1377	,
		1385	,
		1376	,
		1371	,
		1374	,
		1373	,
		1386	,
		1383	,
		1383	,
		1392	,
		1396	,
		1392	,
		1394	,
		1404	,
		1405	,
		1414	,
		1414	,
		1411	,
		1415	,
		1420	,
		1421	,
		1414	,
		1415	,
		1421	,
		1413	,
		1418	,
		1427	,
		1433	,
		1447	,
		1453	,
		1450	,
		1455	,
		1465	,
		1464	,
		1466	,
		1470	,
		1475	,
		1475	,
		1475	,
		1468	,
		1467	,
		1470	,
		1477	,
		1481	,
		1487	,
		1489	,
		1496	,
		1496	,
		1510	,
		1504	,
		1507	,
		1514	,
		1519	,
		1520	,
		1527	,
		1523	,
		1527	,
		1531	,
		1533	,
		1537	,
		1538	,
		1544	,
		1550	,
		1555	,
		1553	,
		1563	,
		1567	,
		1570	,
		1573	,
		1571	,
		1574	,
		1581	,
		1578	,
		1579	,
		1582	,
		1583	,
		1587	,
		1592	,
		1596	,
		1606	,
		1609	,
		1618	,
		1623	,
		1621	,
		1627	,
		1625	,
		1633	,
		1629	,
		1632	,
		1637	,
		1644	,
		1659	,
		1657	,
		1666	,
		1676	,
		1673	,
		1678	,
		1680	,
		1683	,
		1679	,
		1680	,
		1691	,
		1691	,
		1703	,
		1708	,
		1709	,
		1710	,
		1708	,
		1718	,
		1720	,
		1720	,
		1732	,
		1736	,
		1750	,
		1754	,
		1750	,
		1749	,
		1753	,
		1755	,
		1759	,
		1753	,
		1757	,
		1755	,
		1753	,
		1754	,
		1759	,
		1769	,
		1780	,
		1794	,
		1800	,
		1805	,
		1806	,
		1802	,
		1804	,
		1802	,
		1800	,
		1803	,
		1803	,
		1802	,
		1799	,
		1799	,
		1793	,
		1797	,
		1795	,
		1796	,
};

const int32_t sin_theta_fixQ11[320]=
{
		40	,
		80	,
		121	,
		161	,
		201	,
		241	,
		281	,
		320	,
		360	,
		400	,
		439	,
		478	,
		517	,
		556	,
		595	,
		633	,
		671	,
		709	,
		746	,
		784	,
		821	,
		857	,
		894	,
		930	,
		965	,
		1001	,
		1036	,
		1070	,
		1104	,
		1138	,
		1171	,
		1204	,
		1236	,
		1268	,
		1299	,
		1330	,
		1360	,
		1390	,
		1419	,
		1448	,
		1476	,
		1504	,
		1531	,
		1557	,
		1583	,
		1608	,
		1633	,
		1657	,
		1680	,
		1703	,
		1725	,
		1746	,
		1767	,
		1787	,
		1806	,
		1825	,
		1843	,
		1860	,
		1876	,
		1892	,
		1907	,
		1921	,
		1935	,
		1948	,
		1960	,
		1971	,
		1982	,
		1991	,
		2000	,
		2009	,
		2016	,
		2023	,
		2029	,
		2034	,
		2038	,
		2042	,
		2044	,
		2046	,
		2048	,
		2048	,
		2048	,
		2046	,
		2044	,
		2042	,
		2038	,
		2034	,
		2029	,
		2023	,
		2016	,
		2009	,
		2000	,
		1991	,
		1982	,
		1971	,
		1960	,
		1948	,
		1935	,
		1921	,
		1907	,
		1892	,
		1876	,
		1860	,
		1843	,
		1825	,
		1806	,
		1787	,
		1767	,
		1746	,
		1725	,
		1703	,
		1680	,
		1657	,
		1633	,
		1608	,
		1583	,
		1557	,
		1531	,
		1504	,
		1476	,
		1448	,
		1419	,
		1390	,
		1360	,
		1330	,
		1299	,
		1268	,
		1236	,
		1204	,
		1171	,
		1138	,
		1104	,
		1070	,
		1036	,
		1001	,
		965	,
		930	,
		894	,
		857	,
		821	,
		784	,
		746	,
		709	,
		671	,
		633	,
		594	,
		556	,
		517	,
		478	,
		439	,
		400	,
		360	,
		320	,
		281	,
		241	,
		201	,
		161	,
		121	,
		80	,
		40	,
		0	,
		-40	,
		-80	,
		-121	,
		-161	,
		-201	,
		-241	,
		-281	,
		-320	,
		-360	,
		-400	,
		-439	,
		-478	,
		-517	,
		-556	,
		-595	,
		-633	,
		-671	,
		-709	,
		-746	,
		-784	,
		-821	,
		-857	,
		-894	,
		-930	,
		-965	,
		-1001	,
		-1036	,
		-1070	,
		-1104	,
		-1138	,
		-1171	,
		-1204	,
		-1236	,
		-1268	,
		-1299	,
		-1330	,
		-1360	,
		-1390	,
		-1419	,
		-1448	,
		-1476	,
		-1504	,
		-1531	,
		-1557	,
		-1583	,
		-1608	,
		-1633	,
		-1657	,
		-1680	,
		-1703	,
		-1725	,
		-1746	,
		-1767	,
		-1787	,
		-1806	,
		-1825	,
		-1843	,
		-1860	,
		-1876	,
		-1892	,
		-1907	,
		-1921	,
		-1935	,
		-1948	,
		-1960	,
		-1971	,
		-1982	,
		-1991	,
		-2000	,
		-2009	,
		-2016	,
		-2023	,
		-2029	,
		-2034	,
		-2038	,
		-2042	,
		-2044	,
		-2046	,
		-2048	,
		-2048	,
		-2048	,
		-2046	,
		-2044	,
		-2042	,
		-2038	,
		-2034	,
		-2029	,
		-2023	,
		-2016	,
		-2009	,
		-2000	,
		-1991	,
		-1982	,
		-1971	,
		-1960	,
		-1948	,
		-1935	,
		-1921	,
		-1907	,
		-1892	,
		-1876	,
		-1860	,
		-1843	,
		-1825	,
		-1806	,
		-1787	,
		-1767	,
		-1746	,
		-1725	,
		-1703	,
		-1680	,
		-1657	,
		-1633	,
		-1608	,
		-1583	,
		-1557	,
		-1531	,
		-1504	,
		-1476	,
		-1448	,
		-1419	,
		-1390	,
		-1360	,
		-1330	,
		-1299	,
		-1268	,
		-1236	,
		-1204	,
		-1171	,
		-1138	,
		-1104	,
		-1070	,
		-1036	,
		-1001	,
		-965	,
		-930	,
		-894	,
		-857	,
		-821	,
		-784	,
		-746	,
		-709	,
		-671	,
		-633	,
		-594	,
		-556	,
		-517	,
		-478	,
		-439	,
		-400	,
		-360	,
		-320	,
		-281	,
		-241	,
		-201	,
		-161	,
		-121	,
		-80	,
		-40	,
		0	,
};

const int32_t cos_theta_fixQ11[320]=
{
		2048	,
		2046	,
		2044	,
		2042	,
		2038	,
		2034	,
		2029	,
		2023	,
		2016	,
		2009	,
		2000	,
		1991	,
		1982	,
		1971	,
		1960	,
		1948	,
		1935	,
		1921	,
		1907	,
		1892	,
		1876	,
		1860	,
		1843	,
		1825	,
		1806	,
		1787	,
		1767	,
		1746	,
		1725	,
		1703	,
		1680	,
		1657	,
		1633	,
		1608	,
		1583	,
		1557	,
		1531	,
		1504	,
		1476	,
		1448	,
		1419	,
		1390	,
		1360	,
		1330	,
		1299	,
		1268	,
		1236	,
		1204	,
		1171	,
		1138	,
		1104	,
		1070	,
		1036	,
		1001	,
		965	,
		930	,
		894	,
		857	,
		821	,
		784	,
		746	,
		709	,
		671	,
		633	,
		594	,
		556	,
		517	,
		478	,
		439	,
		400	,
		360	,
		320	,
		281	,
		241	,
		201	,
		161	,
		121	,
		80	,
		40	,
		0	,
		-40	,
		-80	,
		-121	,
		-161	,
		-201	,
		-241	,
		-281	,
		-320	,
		-360	,
		-400	,
		-439	,
		-478	,
		-517	,
		-556	,
		-595	,
		-633	,
		-671	,
		-709	,
		-746	,
		-784	,
		-821	,
		-857	,
		-894	,
		-930	,
		-965	,
		-1001	,
		-1036	,
		-1070	,
		-1104	,
		-1138	,
		-1171	,
		-1204	,
		-1236	,
		-1268	,
		-1299	,
		-1330	,
		-1360	,
		-1390	,
		-1419	,
		-1448	,
		-1476	,
		-1504	,
		-1531	,
		-1557	,
		-1583	,
		-1608	,
		-1633	,
		-1657	,
		-1680	,
		-1703	,
		-1725	,
		-1746	,
		-1767	,
		-1787	,
		-1806	,
		-1825	,
		-1843	,
		-1860	,
		-1876	,
		-1892	,
		-1907	,
		-1921	,
		-1935	,
		-1948	,
		-1960	,
		-1971	,
		-1982	,
		-1991	,
		-2000	,
		-2009	,
		-2016	,
		-2023	,
		-2029	,
		-2034	,
		-2038	,
		-2042	,
		-2044	,
		-2046	,
		-2048	,
		-2048	,
		-2048	,
		-2046	,
		-2044	,
		-2042	,
		-2038	,
		-2034	,
		-2029	,
		-2023	,
		-2016	,
		-2009	,
		-2000	,
		-1991	,
		-1982	,
		-1971	,
		-1960	,
		-1948	,
		-1935	,
		-1921	,
		-1907	,
		-1892	,
		-1876	,
		-1860	,
		-1843	,
		-1825	,
		-1806	,
		-1787	,
		-1767	,
		-1746	,
		-1725	,
		-1703	,
		-1680	,
		-1657	,
		-1633	,
		-1608	,
		-1583	,
		-1557	,
		-1531	,
		-1504	,
		-1476	,
		-1448	,
		-1419	,
		-1390	,
		-1360	,
		-1330	,
		-1299	,
		-1268	,
		-1236	,
		-1204	,
		-1171	,
		-1138	,
		-1104	,
		-1070	,
		-1036	,
		-1001	,
		-965	,
		-930	,
		-894	,
		-857	,
		-821	,
		-784	,
		-746	,
		-709	,
		-671	,
		-633	,
		-594	,
		-556	,
		-517	,
		-478	,
		-439	,
		-400	,
		-360	,
		-320	,
		-281	,
		-241	,
		-201	,
		-161	,
		-121	,
		-80	,
		-40	,
		0	,
		40	,
		80	,
		121	,
		161	,
		201	,
		241	,
		281	,
		320	,
		360	,
		400	,
		439	,
		478	,
		517	,
		556	,
		595	,
		633	,
		671	,
		709	,
		746	,
		784	,
		821	,
		857	,
		894	,
		930	,
		965	,
		1001	,
		1036	,
		1070	,
		1104	,
		1138	,
		1171	,
		1204	,
		1236	,
		1268	,
		1299	,
		1330	,
		1360	,
		1390	,
		1419	,
		1448	,
		1476	,
		1504	,
		1531	,
		1557	,
		1583	,
		1608	,
		1633	,
		1657	,
		1680	,
		1703	,
		1725	,
		1746	,
		1767	,
		1787	,
		1806	,
		1825	,
		1843	,
		1860	,
		1876	,
		1892	,
		1907	,
		1921	,
		1935	,
		1948	,
		1960	,
		1971	,
		1982	,
		1991	,
		2000	,
		2009	,
		2016	,
		2023	,
		2029	,
		2034	,
		2038	,
		2042	,
		2044	,
		2046	,
		2048	,
		2048	,

};

const float sinOL[321]=
{
		0	,
		0.019632932	,
		0.039258295	,
		0.058868525	,
		0.078456061	,
		0.098013354	,
		0.117532864	,
		0.137007065	,
		0.156428453	,
		0.175789538	,
		0.195082859	,
		0.214300977	,
		0.233436485	,
		0.252482006	,
		0.271430197	,
		0.290273755	,
		0.309005416	,
		0.327617958	,
		0.346104207	,
		0.364457037	,
		0.382669372	,
		0.400734193	,
		0.418644535	,
		0.436393494	,
		0.453974228	,
		0.47137996	,
		0.48860398	,
		0.505639649	,
		0.522480398	,
		0.539119738	,
		0.555551252	,
		0.571768608	,
		0.587765553	,
		0.603535921	,
		0.619073632	,
		0.634372697	,
		0.649427218	,
		0.664231392	,
		0.678779512	,
		0.69306597	,
		0.707085259	,
		0.720831974	,
		0.734300816	,
		0.747486592	,
		0.760384221	,
		0.77298873	,
		0.785295261	,
		0.797299068	,
		0.808995525	,
		0.820380124	,
		0.831448474	,
		0.842196311	,
		0.85261949	,
		0.862713993	,
		0.872475929	,
		0.881901535	,
		0.890987178	,
		0.899729355	,
		0.908124696	,
		0.916169965	,
		0.92386206	,
		0.931198016	,
		0.938175006	,
		0.944790339	,
		0.951041466	,
		0.956925977	,
		0.962441603	,
		0.967586219	,
		0.97235784	,
		0.976754628	,
		0.980774888	,
		0.984417069	,
		0.987679769	,
		0.990561728	,
		0.993061837	,
		0.995179131	,
		0.996912795	,
		0.998262159	,
		0.999226704	,
		0.999806058	,
		0.999999998	,
		0.999808449	,
		0.999231484	,
		0.998269326	,
		0.996922347	,
		0.995191064	,
		0.993076146	,
		0.990578408	,
		0.987698813	,
		0.984438471	,
		0.980798638	,
		0.976780719	,
		0.97238626	,
		0.967616958	,
		0.962474649	,
		0.956961317	,
		0.951079087	,
		0.944830226	,
		0.938217143	,
		0.931242388	,
		0.923908649	,
		0.916218753	,
		0.908175665	,
		0.899782485	,
		0.891042448	,
		0.881958924	,
		0.872535415	,
		0.862775553	,
		0.8526831	,
		0.842261947	,
		0.831516111	,
		0.820449735	,
		0.809067084	,
		0.797372547	,
		0.785370631	,
		0.773065963	,
		0.760463287	,
		0.747567461	,
		0.734383455	,
		0.720916352	,
		0.707171344	,
		0.693153729	,
		0.678868911	,
		0.664322397	,
		0.649519793	,
		0.634466806	,
		0.619169239	,
		0.60363299	,
		0.587864046	,
		0.571868487	,
		0.555652479	,
		0.539222273	,
		0.522584202	,
		0.505744681	,
		0.488710201	,
		0.471487329	,
		0.454082703	,
		0.436503033	,
		0.418755097	,
		0.400845734	,
		0.38278185	,
		0.364570407	,
		0.346218427	,
		0.327732983	,
		0.309121202	,
		0.290390258	,
		0.271547371	,
		0.252599806	,
		0.233554867	,
		0.214419894	,
		0.195202266	,
		0.175909388	,
		0.1565487	,
		0.137127663	,
		0.117653766	,
		0.098134514	,
		0.078577433	,
		0.05899006	,
		0.039379948	,
		0.019754655	,
		0.000121747	,
		-0.019511208	,
		-0.039136642	,
		-0.058746988	,
		-0.078334689	,
		-0.097892192	,
		-0.117411959	,
		-0.136886465	,
		-0.156308203	,
		-0.175669686	,
		-0.19496345	,
		-0.214182057	,
		-0.2333181	,
		-0.252364201	,
		-0.271313018	,
		-0.290157248	,
		-0.308889624	,
		-0.327502928	,
		-0.345989982	,
		-0.364343661	,
		-0.382556889	,
		-0.400622646	,
		-0.418533967	,
		-0.436283948	,
		-0.453865746	,
		-0.471272584	,
		-0.488497751	,
		-0.505534608	,
		-0.522376587	,
		-0.539017195	,
		-0.555450018	,
		-0.571668721	,
		-0.587667051	,
		-0.603438843	,
		-0.618978015	,
		-0.634278578	,
		-0.649334634	,
		-0.664140378	,
		-0.678690103	,
		-0.692978201	,
		-0.706999163	,
		-0.720747584	,
		-0.734218165	,
		-0.747405713	,
		-0.760305144	,
		-0.772911486	,
		-0.785219879	,
		-0.797225578	,
		-0.808923955	,
		-0.8203105	,
		-0.831380825	,
		-0.842130662	,
		-0.852555866	,
		-0.86265242	,
		-0.87241643	,
		-0.881844133	,
		-0.890931895	,
		-0.899676212	,
		-0.908073714	,
		-0.916121163	,
		-0.923815457	,
		-0.931153631	,
		-0.938132855	,
		-0.944750439	,
		-0.951003832	,
		-0.956890623	,
		-0.962408543	,
		-0.967555465	,
		-0.972329405	,
		-0.976728523	,
		-0.980751122	,
		-0.984395653	,
		-0.987660709	,
		-0.990545033	,
		-0.993047513	,
		-0.995167184	,
		-0.996903228	,
		-0.998254977	,
		-0.99922191	,
		-0.999803653	,
		-0.999999983	,
		-0.999810824	,
		-0.999236249	,
		-0.998276479	,
		-0.996931884	,
		-0.995202982	,
		-0.993090441	,
		-0.990595074	,
		-0.987717843	,
		-0.984459858	,
		-0.980822375	,
		-0.976806795	,
		-0.972414666	,
		-0.967647682	,
		-0.962507681	,
		-0.956996643	,
		-0.951116693	,
		-0.944870099	,
		-0.938259267	,
		-0.931286746	,
		-0.923955224	,
		-0.916267528	,
		-0.90822662	,
		-0.899835601	,
		-0.891097705	,
		-0.882016301	,
		-0.872594888	,
		-0.8628371	,
		-0.852746698	,
		-0.842327571	,
		-0.831583736	,
		-0.820519334	,
		-0.809138631	,
		-0.797446014	,
		-0.78544599	,
		-0.773143185	,
		-0.760542342	,
		-0.747648318	,
		-0.734466084	,
		-0.72100072	,
		-0.707257419	,
		-0.693241478	,
		-0.6789583	,
		-0.664413391	,
		-0.649612358	,
		-0.634560906	,
		-0.619264838	,
		-0.60373005	,
		-0.58796253	,
		-0.571968357	,
		-0.555753697	,
		-0.5393248	,
		-0.522687999	,
		-0.505849707	,
		-0.488816416	,
		-0.471594691	,
		-0.454191172	,
		-0.436612566	,
		-0.418865652	,
		-0.400957269	,
		-0.382894322	,
		-0.364683773	,
		-0.346332642	,
		-0.327848004	,
		-0.309236984	,
		-0.290506757	,
		-0.271664542	,
		-0.252717603	,
		-0.233673245	,
		-0.214538808	,
		-0.195321669	,
		-0.176029236	,
		-0.156668945	,
		-0.137248259	,
		-0.117774667	,
		-0.098255673	,
		-0.078698803	,
		-0.059111595	,
		-0.0395016	,
		-0.019876378	,
		0
};

const uint32_t sinOLuint[321]=
{
		1875	,
		1838	,
		1801	,
		1765	,
		1728	,
		1691	,
		1655	,
		1618	,
		1582	,
		1545	,
		1509	,
		1473	,
		1437	,
		1402	,
		1366	,
		1331	,
		1296	,
		1261	,
		1226	,
		1192	,
		1158	,
		1124	,
		1090	,
		1057	,
		1024	,
		991	,
		959	,
		927	,
		896	,
		864	,
		834	,
		803	,
		773	,
		744	,
		715	,
		686	,
		658	,
		630	,
		603	,
		576	,
		550	,
		524	,
		499	,
		474	,
		450	,
		426	,
		403	,
		380	,
		359	,
		337	,
		316	,
		296	,
		277	,
		258	,
		240	,
		222	,
		205	,
		188	,
		173	,
		158	,
		143	,
		129	,
		116	,
		104	,
		92	,
		81	,
		71	,
		61	,
		52	,
		44	,
		37	,
		30	,
		24	,
		18	,
		14	,
		10	,
		6	,
		4	,
		2	,
		1	,
		1	,
		1	,
		2	,
		4	,
		6	,
		10	,
		13	,
		18	,
		24	,
		30	,
		36	,
		44	,
		52	,
		61	,
		71	,
		81	,
		92	,
		104	,
		116	,
		129	,
		143	,
		158	,
		173	,
		188	,
		205	,
		222	,
		239	,
		258	,
		277	,
		296	,
		316	,
		337	,
		358	,
		380	,
		403	,
		426	,
		450	,
		474	,
		498	,
		524	,
		549	,
		576	,
		602	,
		630	,
		657	,
		686	,
		714	,
		743	,
		773	,
		803	,
		833	,
		864	,
		895	,
		927	,
		959	,
		991	,
		1024	,
		1057	,
		1090	,
		1124	,
		1157	,
		1192	,
		1226	,
		1261	,
		1296	,
		1331	,
		1366	,
		1402	,
		1437	,
		1473	,
		1509	,
		1545	,
		1582	,
		1618	,
		1654	,
		1691	,
		1728	,
		1764	,
		1801	,
		1838	,
		1875	,
		1912	,
		1948	,
		1985	,
		2022	,
		2058	,
		2095	,
		2132	,
		2168	,
		2204	,
		2240	,
		2276	,
		2312	,
		2348	,
		2384	,
		2419	,
		2454	,
		2489	,
		2524	,
		2558	,
		2592	,
		2626	,
		2660	,
		2693	,
		2726	,
		2758	,
		2791	,
		2823	,
		2854	,
		2885	,
		2916	,
		2947	,
		2977	,
		3006	,
		3035	,
		3064	,
		3092	,
		3120	,
		3147	,
		3174	,
		3200	,
		3226	,
		3251	,
		3276	,
		3300	,
		3324	,
		3347	,
		3369	,
		3391	,
		3413	,
		3433	,
		3454	,
		3473	,
		3492	,
		3510	,
		3528	,
		3545	,
		3561	,
		3577	,
		3592	,
		3607	,
		3620	,
		3634	,
		3646	,
		3658	,
		3669	,
		3679	,
		3689	,
		3698	,
		3706	,
		3713	,
		3720	,
		3726	,
		3732	,
		3736	,
		3740	,
		3744	,
		3746	,
		3748	,
		3748	,
		3748	,
		3748	,
		3748	,
		3746	,
		3744	,
		3741	,
		3737	,
		3732	,
		3726	,
		3720	,
		3714	,
		3706	,
		3698	,
		3689	,
		3679	,
		3669	,
		3658	,
		3646	,
		3634	,
		3621	,
		3607	,
		3593	,
		3577	,
		3562	,
		3545	,
		3528	,
		3511	,
		3492	,
		3473	,
		3454	,
		3434	,
		3413	,
		3392	,
		3370	,
		3347	,
		3324	,
		3301	,
		3276	,
		3252	,
		3227	,
		3201	,
		3174	,
		3148	,
		3120	,
		3093	,
		3064	,
		3036	,
		3007	,
		2977	,
		2947	,
		2917	,
		2886	,
		2855	,
		2823	,
		2791	,
		2759	,
		2726	,
		2693	,
		2660	,
		2627	,
		2593	,
		2559	,
		2524	,
		2490	,
		2455	,
		2420	,
		2384	,
		2349	,
		2313	,
		2277	,
		2241	,
		2205	,
		2169	,
		2132	,
		2096	,
		2059	,
		2023	,
		1986	,
		1949	,
		1912	,
		1875
};

const int32_t sinOLint[321] =
{
		0	,
		73	,
		147	,
		220	,
		294	,
		367	,
		440	,
		513	,
		586	,
		659	,
		731	,
		803	,
		875	,
		946	,
		1017	,
		1088	,
		1158	,
		1228	,
		1297	,
		1366	,
		1434	,
		1502	,
		1569	,
		1636	,
		1701	,
		1767	,
		1831	,
		1895	,
		1958	,
		2021	,
		2082	,
		2143	,
		2203	,
		2262	,
		2320	,
		2378	,
		2434	,
		2490	,
		2544	,
		2598	,
		2650	,
		2702	,
		2752	,
		2802	,
		2850	,
		2897	,
		2944	,
		2989	,
		3032	,
		3075	,
		3117	,
		3157	,
		3196	,
		3234	,
		3270	,
		3306	,
		3340	,
		3373	,
		3404	,
		3434	,
		3463	,
		3491	,
		3517	,
		3542	,
		3565	,
		3587	,
		3608	,
		3627	,
		3645	,
		3661	,
		3676	,
		3690	,
		3702	,
		3713	,
		3722	,
		3730	,
		3737	,
		3742	,
		3746	,
		3748	,
		3748	,
		3748	,
		3746	,
		3742	,
		3737	,
		3730	,
		3723	,
		3713	,
		3702	,
		3690	,
		3677	,
		3661	,
		3645	,
		3627	,
		3608	,
		3587	,
		3565	,
		3542	,
		3517	,
		3491	,
		3463	,
		3434	,
		3404	,
		3373	,
		3340	,
		3306	,
		3271	,
		3234	,
		3196	,
		3157	,
		3117	,
		3075	,
		3033	,
		2989	,
		2944	,
		2898	,
		2850	,
		2802	,
		2753	,
		2702	,
		2651	,
		2598	,
		2545	,
		2490	,
		2435	,
		2378	,
		2321	,
		2263	,
		2203	,
		2143	,
		2083	,
		2021	,
		1959	,
		1896	,
		1832	,
		1767	,
		1702	,
		1636	,
		1569	,
		1502	,
		1435	,
		1366	,
		1297	,
		1228	,
		1158	,
		1088	,
		1018	,
		946	,
		875	,
		803	,
		731	,
		659	,
		586	,
		514	,
		441	,
		367	,
		294	,
		221	,
		147	,
		74	,
		0	,
		-74	,
		-147	,
		-221	,
		-294	,
		-367	,
		-441	,
		-514	,
		-586	,
		-659	,
		-731	,
		-803	,
		-875	,
		-947	,
		-1018	,
		-1088	,
		-1159	,
		-1228	,
		-1298	,
		-1366	,
		-1435	,
		-1502	,
		-1570	,
		-1636	,
		-1702	,
		-1767	,
		-1832	,
		-1896	,
		-1959	,
		-2021	,
		-2083	,
		-2144	,
		-2204	,
		-2263	,
		-2321	,
		-2378	,
		-2435	,
		-2490	,
		-2545	,
		-2598	,
		-2651	,
		-2703	,
		-2753	,
		-2803	,
		-2851	,
		-2898	,
		-2944	,
		-2989	,
		-3033	,
		-3076	,
		-3117	,
		-3158	,
		-3197	,
		-3235	,
		-3271	,
		-3307	,
		-3341	,
		-3373	,
		-3405	,
		-3435	,
		-3464	,
		-3491	,
		-3518	,
		-3542	,
		-3566	,
		-3588	,
		-3609	,
		-3628	,
		-3646	,
		-3662	,
		-3677	,
		-3691	,
		-3703	,
		-3714	,
		-3723	,
		-3731	,
		-3738	,
		-3743	,
		-3747	,
		-3748	,
		-3748	,
		-3748	,
		-3747	,
		-3743	,
		-3738	,
		-3732	,
		-3724	,
		-3714	,
		-3703	,
		-3691	,
		-3678	,
		-3663	,
		-3646	,
		-3628	,
		-3609	,
		-3588	,
		-3566	,
		-3543	,
		-3518	,
		-3492	,
		-3464	,
		-3436	,
		-3405	,
		-3374	,
		-3341	,
		-3307	,
		-3272	,
		-3235	,
		-3197	,
		-3158	,
		-3118	,
		-3077	,
		-3034	,
		-2990	,
		-2945	,
		-2899	,
		-2852	,
		-2803	,
		-2754	,
		-2704	,
		-2652	,
		-2599	,
		-2546	,
		-2491	,
		-2436	,
		-2379	,
		-2322	,
		-2264	,
		-2205	,
		-2145	,
		-2084	,
		-2022	,
		-1960	,
		-1897	,
		-1833	,
		-1769	,
		-1703	,
		-1637	,
		-1571	,
		-1504	,
		-1436	,
		-1368	,
		-1299	,
		-1230	,
		-1160	,
		-1090	,
		-1019	,
		-948	,
		-877	,
		-805	,
		-733	,
		-660	,
		-588	,
		-515	,
		-442	,
		-369	,
		-296	,
		-222	,
		-149	,
		-75	,
		0
};

const int32_t sinOLint8[321]=
{
	1	,
	58	,
	117	,
	176	,
	235	,
	293	,
	352	,
	410	,
	468	,
	527	,
	584	,
	642	,
	700	,
	756	,
	813	,
	870	,
	926	,
	982	,
	1037	,
	1092	,
	1147	,
	1201	,
	1255	,
	1308	,
	1360	,
	1413	,
	1464	,
	1516	,
	1566	,
	1616	,
	1665	,
	1714	,
	1762	,
	1809	,
	1856	,
	1902	,
	1947	,
	1992	,
	2035	,
	2078	,
	2120	,
	2161	,
	2201	,
	2241	,
	2280	,
	2317	,
	2355	,
	2391	,
	2425	,
	2460	,
	2493	,
	2525	,
	2556	,
	2587	,
	2616	,
	2644	,
	2672	,
	2698	,
	2723	,
	2747	,
	2770	,
	2792	,
	2813	,
	2833	,
	2852	,
	2869	,
	2886	,
	2901	,
	2916	,
	2928	,
	2940	,
	2952	,
	2961	,
	2970	,
	2977	,
	2984	,
	2989	,
	2993	,
	2996	,
	2998	,
	2998	,
	2998	,
	2996	,
	2993	,
	2989	,
	2984	,
	2978	,
	2970	,
	2961	,
	2952	,
	2941	,
	2928	,
	2916	,
	2901	,
	2886	,
	2869	,
	2852	,
	2833	,
	2813	,
	2792	,
	2770	,
	2747	,
	2723	,
	2698	,
	2672	,
	2644	,
	2616	,
	2587	,
	2556	,
	2525	,
	2493	,
	2460	,
	2426	,
	2391	,
	2355	,
	2318	,
	2280	,
	2241	,
	2202	,
	2161	,
	2120	,
	2078	,
	2036	,
	1992	,
	1948	,
	1902	,
	1856	,
	1810	,
	1762	,
	1714	,
	1666	,
	1616	,
	1567	,
	1516	,
	1465	,
	1413	,
	1361	,
	1308	,
	1255	,
	1201	,
	1148	,
	1092	,
	1037	,
	982	,
	926	,
	870	,
	814	,
	756	,
	700	,
	642	,
	584	,
	527	,
	468	,
	411	,
	352	,
	293	,
	235	,
	176	,
	117	,
	59	,
	1	,
	-60	,
	-118	,
	-177	,
	-236	,
	-294	,
	-353	,
	-412	,
	-469	,
	-528	,
	-585	,
	-643	,
	-700	,
	-758	,
	-815	,
	-871	,
	-928	,
	-983	,
	-1039	,
	-1093	,
	-1148	,
	-1202	,
	-1256	,
	-1309	,
	-1362	,
	-1414	,
	-1466	,
	-1517	,
	-1568	,
	-1617	,
	-1667	,
	-1716	,
	-1764	,
	-1811	,
	-1857	,
	-1903	,
	-1948	,
	-1992	,
	-2036	,
	-2079	,
	-2121	,
	-2163	,
	-2203	,
	-2243	,
	-2281	,
	-2319	,
	-2356	,
	-2392	,
	-2427	,
	-2461	,
	-2494	,
	-2527	,
	-2558	,
	-2588	,
	-2617	,
	-2646	,
	-2673	,
	-2699	,
	-2724	,
	-2748	,
	-2772	,
	-2793	,
	-2815	,
	-2834	,
	-2853	,
	-2871	,
	-2888	,
	-2903	,
	-2917	,
	-2930	,
	-2942	,
	-2953	,
	-2963	,
	-2972	,
	-2979	,
	-2985	,
	-2991	,
	-2995	,
	-2998	,
	-3000	,
	-3000	,
	-3000	,
	-2998	,
	-2995	,
	-2991	,
	-2986	,
	-2980	,
	-2972	,
	-2963	,
	-2953	,
	-2943	,
	-2931	,
	-2917	,
	-2903	,
	-2888	,
	-2871	,
	-2853	,
	-2835	,
	-2815	,
	-2794	,
	-2772	,
	-2749	,
	-2724	,
	-2700	,
	-2673	,
	-2646	,
	-2618	,
	-2588	,
	-2558	,
	-2527	,
	-2495	,
	-2462	,
	-2428	,
	-2392	,
	-2356	,
	-2320	,
	-2282	,
	-2243	,
	-2204	,
	-2164	,
	-2122	,
	-2080	,
	-2037	,
	-1993	,
	-1949	,
	-1904	,
	-1858	,
	-1812	,
	-1764	,
	-1716	,
	-1668	,
	-1618	,
	-1568	,
	-1518	,
	-1467	,
	-1416	,
	-1363	,
	-1310	,
	-1257	,
	-1204	,
	-1149	,
	-1095	,
	-1040	,
	-984	,
	-928	,
	-872	,
	-816	,
	-759	,
	-702	,
	-644	,
	-587	,
	-528	,
	-471	,
	-412	,
	-354	,
	-296	,
	-237	,
	-178	,
	-120	,
	-60	,
	1
};

const int32_t sinOLint94[321]=
{
	0	,
	68	,
	138	,
	206	,
	276	,
	344	,
	413	,
	482	,
	550	,
	619	,
	687	,
	754	,
	822	,
	889	,
	955	,
	1022	,
	1088	,
	1154	,
	1219	,
	1284	,
	1347	,
	1411	,
	1474	,
	1537	,
	1598	,
	1660	,
	1721	,
	1781	,
	1840	,
	1899	,
	1957	,
	2014	,
	2070	,
	2126	,
	2180	,
	2235	,
	2287	,
	2340	,
	2391	,
	2442	,
	2491	,
	2539	,
	2586	,
	2633	,
	2679	,
	2723	,
	2767	,
	2809	,
	2850	,
	2890	,
	2929	,
	2967	,
	3004	,
	3039	,
	3073	,
	3107	,
	3139	,
	3170	,
	3199	,
	3227	,
	3255	,
	3281	,
	3305	,
	3329	,
	3351	,
	3371	,
	3391	,
	3409	,
	3426	,
	3441	,
	3455	,
	3468	,
	3479	,
	3490	,
	3498	,
	3506	,
	3512	,
	3517	,
	3521	,
	3523	,
	3523	,
	3523	,
	3521	,
	3517	,
	3512	,
	3506	,
	3499	,
	3490	,
	3479	,
	3468	,
	3456	,
	3441	,
	3426	,
	3409	,
	3391	,
	3371	,
	3351	,
	3329	,
	3305	,
	3281	,
	3255	,
	3227	,
	3199	,
	3170	,
	3139	,
	3107	,
	3074	,
	3039	,
	3004	,
	2967	,
	2929	,
	2890	,
	2851	,
	2809	,
	2767	,
	2724	,
	2679	,
	2633	,
	2587	,
	2539	,
	2491	,
	2442	,
	2392	,
	2340	,
	2288	,
	2235	,
	2181	,
	2127	,
	2070	,
	2014	,
	1958	,
	1899	,
	1841	,
	1782	,
	1722	,
	1660	,
	1599	,
	1537	,
	1474	,
	1411	,
	1348	,
	1284	,
	1219	,
	1154	,
	1088	,
	1022	,
	956	,
	889	,
	822	,
	754	,
	687	,
	619	,
	550	,
	483	,
	414	,
	344	,
	276	,
	207	,
	138	,
	69	,
	0	,
	-70	,
	-139	,
	-208	,
	-277	,
	-345	,
	-415	,
	-484	,
	-551	,
	-620	,
	-688	,
	-755	,
	-823	,
	-891	,
	-957	,
	-1023	,
	-1090	,
	-1155	,
	-1221	,
	-1285	,
	-1349	,
	-1412	,
	-1476	,
	-1538	,
	-1600	,
	-1661	,
	-1723	,
	-1783	,
	-1842	,
	-1900	,
	-1959	,
	-2016	,
	-2072	,
	-2128	,
	-2182	,
	-2236	,
	-2289	,
	-2341	,
	-2393	,
	-2443	,
	-2492	,
	-2541	,
	-2588	,
	-2635	,
	-2680	,
	-2725	,
	-2768	,
	-2810	,
	-2852	,
	-2892	,
	-2930	,
	-2969	,
	-3006	,
	-3041	,
	-3075	,
	-3109	,
	-3141	,
	-3171	,
	-3201	,
	-3229	,
	-3257	,
	-3282	,
	-3307	,
	-3330	,
	-3353	,
	-3373	,
	-3393	,
	-3411	,
	-3428	,
	-3443	,
	-3457	,
	-3470	,
	-3481	,
	-3492	,
	-3500	,
	-3508	,
	-3514	,
	-3519	,
	-3523	,
	-3525	,
	-3525	,
	-3525	,
	-3523	,
	-3519	,
	-3514	,
	-3509	,
	-3501	,
	-3492	,
	-3481	,
	-3470	,
	-3458	,
	-3444	,
	-3428	,
	-3411	,
	-3393	,
	-3373	,
	-3353	,
	-3331	,
	-3307	,
	-3283	,
	-3257	,
	-3230	,
	-3201	,
	-3172	,
	-3141	,
	-3109	,
	-3076	,
	-3041	,
	-3006	,
	-2969	,
	-2931	,
	-2893	,
	-2852	,
	-2811	,
	-2769	,
	-2726	,
	-2681	,
	-2635	,
	-2589	,
	-2542	,
	-2493	,
	-2444	,
	-2394	,
	-2342	,
	-2290	,
	-2237	,
	-2183	,
	-2129	,
	-2073	,
	-2017	,
	-1959	,
	-1901	,
	-1843	,
	-1784	,
	-1724	,
	-1663	,
	-1601	,
	-1539	,
	-1477	,
	-1414	,
	-1350	,
	-1286	,
	-1222	,
	-1157	,
	-1091	,
	-1025	,
	-958	,
	-892	,
	-825	,
	-757	,
	-690	,
	-621	,
	-553	,
	-485	,
	-416	,
	-347	,
	-279	,
	-209	,
	-141	,
	-71	,
	0
};

const long int sin_fixed[321]=
{
	0,
	1286,
	2572,
	3857,
	5141,
	6423,
	7702,
	8978,
	10251,
	11520,
	12784,
	14043,
	15297,
	16546,
	17787,
	19022,
	20250,
	21470,
	22681,
	23884,
	25077,
	26261,
	27435,
	28598,
	29750,
	30891,
	32020,
	33136,
	34240,
	35330,
	36407,
	37470,
	38518,
	39552,
	40570,
	41573,
	42559,
	43529,
	44483,
	45419,
	46338,
	47239,
	48121,
	48985,
	49831,
	50657,
	51463,
	52250,
	53017,
	53763,
	54488,
	55192,
	55876,
	56537,
	57177,
	57795,
	58390,
	58963,
	59513,
	60041,
	60545,
	61025,
	61483,
	61916,
	62326,
	62712,
	63073,
	63410,
	63723,
	64011,
	64275,
	64514,
	64728,
	64917,
	65080,
	65219,
	65333,
	65421,
	65485,
	65523,
	65535,
	65523,
	65485,
	65422,
	65334,
	65221,
	65082,
	64919,
	64730,
	64516,
	64278,
	64015,
	63727,
	63414,
	63077,
	62716,
	62331,
	61921,
	61488,
	61031,
	60550,
	60047,
	59520,
	58970,
	58397,
	57802,
	57184,
	56545,
	55883,
	55201,
	54496,
	53771,
	53025,
	52259,
	51473,
	50666,
	49841,
	48996,
	48132,
	47249,
	46348,
	45430,
	44494,
	43541,
	42571,
	41584,
	40582,
	39564,
	38530,
	37482,
	36420,
	35343,
	34253,
	33149,
	32033,
	30904,
	29764,
	28612,
	27449,
	26275,
	25091,
	23898,
	22695,
	21484,
	20264,
	19037,
	17802,
	16560,
	15312,
	14058,
	12799,
	11535,
	10266,
	8993,
	7717,
	6438,
	5156,
	3873,
	2587,
	1301,
	0,
	-1272,
	-2558,
	-3843,
	-5127,
	-6409,
	-7688
	-8964,
	-10237,
	-11506,
	-12770,
	-14030,
	-15284,
	-16532,
	-17774,
	-19009,
	-20236,
	-21456,
	-22668,
	-23871,
	-25064,
	-26248,
	-27422,
	-28585,
	-29738,
	-30878,
	-32007,
	-33124,
	-34228,
	-35318,
	-36395,
	-37458,
	-38507,
	-39541,
	-40559,
	-41562,
	-42549,
	-43519,
	-44473,
	-45409,
	-46328,
	-47229,
	-48112,
	-48976,
	-49822,
	-50648,
	-51455,
	-52242,
	-53009,
	-53755,
	-54481,
	-55185,
	-55869,
	-56530,
	-57170,
	-57788,
	-58384,
	-58957,
	-59508,
	-60035,
	-60540,
	-61021,
	-61479,
	-61912,
	-62322,
	-62708,
	-63070,
	-63408,
	-63721,
	-64009,
	-64273,
	-64512,
	-64726,
	-64915,
	-65080,
	-65219,
	-65333,
	-65422,
	-65485,
	-65523,
	-65536,
	-65524,
	-65487,
	-65424,
	-65336,
	-65223,
	-65085,
	-64922,
	-64733,
	-64520,
	-64282,
	-64019,
	-63731,
	-63419,
	-63082,
	-62722,
	-62336,
	-61927,
	-61494,
	-61038,
	-60557,
	-60054,
	-59527,
	-58977,
	-58405,
	-57810,
	-57193,
	-56553,
	-55892,
	-55210,
	-54506,
	-53781,
	-53035,
	-52269,
	-51483,
	-50677,
	-49851,
	-49007,
	-48143,
	-47261,
	-46360,
	-45442,
	-44506,
	-43553,
	-42583,
	-41597,
	-40595,
	-39577,
	-38544,
	-37496,
	-36433,
	-35357,
	-34267,
	-33163,
	-32047,
	-30919,
	-29778,
	-28626,
	-27463,
	-26290,
	-25106,
	-23913,
	-22710,
	-21499,
	-20280,
	-19052,
	-17818,
	-16576,
	-15328,
	-14074,
	-12815,
	-11551,
	-10282,
	-9009,
	-7733,
	-6454,
	-5172,
	-3889,
	-2604,
	-1317,
	0
};

const long int cos_fixed[321]=
{
65536,
65523,
65485,
65422,
65334,
65220,
65081,
64918,
64729,
64515,
64276,
64013,
63725,
63412,
63075,
62714,
62328,
61919,
61485,
61028,
60548,
60044,
59516,
58966,
58394,
57798,
57181,
56541,
55880,
55197,
54492,
53767,
53021,
52255,
51468,
50662,
49836,
48991,
48127,
47244,
46343,
45424,
44488,
43535,
42565,
41578,
40576,
39558,
38524,
37476,
36413,
35337,
34246,
33143,
32026,
30898,
29757,
28605,
27442,
26268,
25084,
23891,
22688,
21477,
20257,
19029,
17795,
16553,
15305,
14051,
12791,
11527,
10258,
8986,
7709,
6430,
5149,
3865,
2580,
1294,
0,
-1280,
-2566,
-3851,
-5134,
-6416,
-7695,
-8972,
-10244,
-11513,
-12778,
-14037,
-15291,
-16539,
-17781,
-19016,
-20244,
-21463,
-22675,
-23878,
-25071,
-26255,
-27429,
-28592,
-29744,
-30885,
-32014,
-33131,
-34234,
-35325,
-36402,
-37465,
-38513,
-39547,
-40565,
-41568,
-42554,
-43525,
-44478,
-45415,
-46333,
-47234,
-48117,
-48981,
-49827,
-50653,
-51460,
-52246,
-53013,
-53759,
-54485,
-55189,
-55873,
-56534,
-57174,
-57792,
-58388,
-58961,
-59511,
-60039,
-60543,
-61024,
-61481,
-61915,
-62325,
-62711,
-63072,
-63410,
-63722,
-64011,
-64274,
-64513,
-64727,
-64916,
-65081,
-65219,
-65333,
-65422,
-65485,
-65524,
-65536,
-65524,
-65487,
-65424,
-65336,
-65222,
-65084,
-64921,
-64732,
-64519,
-64280,
-64017,
-63730,
-63417,
-63080,
-62719,
-62334,
-61925,
-61492,
-61035,
-60554,
-60051,
-59524,
-58974,
-58401,
-57806,
-57189,
-56550,
-55888,
-55206,
-54502,
-53777,
-53031,
-52265,
-51478,
-50672,
-49847,
-49002,
-48138,
-47255,
-46355,
-45436,
-44500,
-43547,
-42577,
-41591,
-40589,
-39571,
-38538,
-37489,
-36427,
-35350,
-34260,
-33157,
-32040,
-30912,
-29771,
-28620,
-27457,
-26283,
-25099,
-23906,
-22703,
-21492,
-20272,
-19045,
-17810,
-16569,
-15321,
-14067,
-12807,
-11543,
-10274,
-9002,
-7725,
-6446,
-5165,
-3881,
-2596,
-1310,
0,
1263,
2550,
3835,
5118,
6400,
7679,
8956,
10228,
11497,
12762,
14021,
15275,
16524,
17765,
19000,
20228,
21448,
22660,
23863,
25056,
26240,
27414,
28578,
29730,
30871,
32000,
33116,
34220,
35311,
36388,
37451,
38500,
39534,
40552,
41555,
42542,
43512,
44466,
45403,
46322,
47223,
48106,
48970,
49816,
50642,
51449,
52236,
53003,
53750,
54475,
55180,
55864,
56526,
57166,
57784,
58380,
58953,
59504,
60031,
60536,
61017,
61475,
61909,
62319,
62705,
63067,
63405,
63718,
64007,
64271,
64510,
64724,
64913,
65078,
65217,
65331,
65420,
65484,
65522,
65536

};


const float sinLUT300[301]=
{
		0			,
		0.020942420	,
		0.041875654	,
		0.062790520	,
		0.083677843	,
		0.104528463	,
		0.125333234	,
		0.146083029	,
		0.166768747	,
		0.187381315	,
		0.207911691	,
		0.228350870	,
		0.248689887	,
		0.268919821	,
		0.289031797	,
		0.309016994	,
		0.328866647	,
		0.348572047	,
		0.368124553	,
		0.387515586	,
		0.406736643	,
		0.425779292	,
		0.444635179	,
		0.463296035	,
		0.481753674	,
		0.500000000	,
		0.518027009	,
		0.535826795	,
		0.553391549	,
		0.570713568	,
		0.587785252	,
		0.604599115	,
		0.621147780	,
		0.637423990	,
		0.653420604	,
		0.669130606	,
		0.684547106	,
		0.699663341	,
		0.714472680	,
		0.728968627	,
		0.743144825	,
		0.756995056	,
		0.770513243	,
		0.783693457	,
		0.796529918	,
		0.809016994	,
		0.821149209	,
		0.832921241	,
		0.844327926	,
		0.855364260	,
		0.866025404	,
		0.876306680	,
		0.886203579	,
		0.895711760	,
		0.904827052	,
		0.913545458	,
		0.921863152	,
		0.929776486	,
		0.937281989	,
		0.944376370	,
		0.951056516	,
		0.957319498	,
		0.963162567	,
		0.968583161	,
		0.973578903	,
		0.978147601	,
		0.982287251	,
		0.985996037	,
		0.989272333	,
		0.992114701	,
		0.994521895	,
		0.996492859	,
		0.998026728	,
		0.999122830	,
		0.999780683	,
		1.000000000	,
		0.999780683	,
		0.999122830	,
		0.998026728	,
		0.996492859	,
		0.994521895	,
		0.992114701	,
		0.989272333	,
		0.985996037	,
		0.982287251	,
		0.978147601	,
		0.973578903	,
		0.968583161	,
		0.963162567	,
		0.957319498	,
		0.951056516	,
		0.944376370	,
		0.937281989	,
		0.929776486	,
		0.921863152	,
		0.913545458	,
		0.904827052	,
		0.895711760	,
		0.886203579	,
		0.876306680	,
		0.866025404	,
		0.855364260	,
		0.844327926	,
		0.832921241	,
		0.821149209	,
		0.809016994	,
		0.796529918	,
		0.783693457	,
		0.770513243	,
		0.756995056	,
		0.743144825	,
		0.728968627	,
		0.714472680	,
		0.699663341	,
		0.684547106	,
		0.669130606	,
		0.653420604	,
		0.637423990	,
		0.621147780	,
		0.604599115	,
		0.587785252	,
		0.570713568	,
		0.553391549	,
		0.535826795	,
		0.518027009	,
		0.500000000	,
		0.481753674	,
		0.463296035	,
		0.444635179	,
		0.425779292	,
		0.406736643	,
		0.387515586	,
		0.368124553	,
		0.348572047	,
		0.328866647	,
		0.309016994	,
		0.289031797	,
		0.268919821	,
		0.248689887	,
		0.228350870	,
		0.207911691	,
		0.187381315	,
		0.166768747	,
		0.146083029	,
		0.125333234	,
		0.104528463	,
		0.083677843	,
		0.062790520	,
		0.041875654	,
		0.020942420	,
		0.000000000	,
		-0.020942420	,
		-0.041875654	,
		-0.062790520	,
		-0.083677843	,
		-0.104528463	,
		-0.125333234	,
		-0.146083029	,
		-0.166768747	,
		-0.187381315	,
		-0.207911691	,
		-0.228350870	,
		-0.248689887	,
		-0.268919821	,
		-0.289031797	,
		-0.309016994	,
		-0.328866647	,
		-0.348572047	,
		-0.368124553	,
		-0.387515586	,
		-0.406736643	,
		-0.425779292	,
		-0.444635179	,
		-0.463296035	,
		-0.481753674	,
		-0.500000000	,
		-0.518027009	,
		-0.535826795	,
		-0.553391549	,
		-0.570713568	,
		-0.587785252	,
		-0.604599115	,
		-0.621147780	,
		-0.637423990	,
		-0.653420604	,
		-0.669130606	,
		-0.684547106	,
		-0.699663341	,
		-0.714472680	,
		-0.728968627	,
		-0.743144825	,
		-0.756995056	,
		-0.770513243	,
		-0.783693457	,
		-0.796529918	,
		-0.809016994	,
		-0.821149209	,
		-0.832921241	,
		-0.844327926	,
		-0.855364260	,
		-0.866025404	,
		-0.876306680	,
		-0.886203579	,
		-0.895711760	,
		-0.904827052	,
		-0.913545458	,
		-0.921863152	,
		-0.929776486	,
		-0.937281989	,
		-0.944376370	,
		-0.951056516	,
		-0.957319498	,
		-0.963162567	,
		-0.968583161	,
		-0.973578903	,
		-0.978147601	,
		-0.982287251	,
		-0.985996037	,
		-0.989272333	,
		-0.992114701	,
		-0.994521895	,
		-0.996492859	,
		-0.998026728	,
		-0.999122830	,
		-0.999780683	,
		-1.000000000	,
		-0.999780683	,
		-0.999122830	,
		-0.998026728	,
		-0.996492859	,
		-0.994521895	,
		-0.992114701	,
		-0.989272333	,
		-0.985996037	,
		-0.982287251	,
		-0.978147601	,
		-0.973578903	,
		-0.968583161	,
		-0.963162567	,
		-0.957319498	,
		-0.951056516	,
		-0.944376370	,
		-0.937281989	,
		-0.929776486	,
		-0.921863152	,
		-0.913545458	,
		-0.904827052	,
		-0.895711760	,
		-0.886203579	,
		-0.876306680	,
		-0.866025404	,
		-0.855364260	,
		-0.844327926	,
		-0.832921241	,
		-0.821149209	,
		-0.809016994	,
		-0.796529918	,
		-0.783693457	,
		-0.770513243	,
		-0.756995056	,
		-0.743144825	,
		-0.728968627	,
		-0.714472680	,
		-0.699663341	,
		-0.684547106	,
		-0.669130606	,
		-0.653420604	,
		-0.637423990	,
		-0.621147780	,
		-0.604599115	,
		-0.587785252	,
		-0.570713568	,
		-0.553391549	,
		-0.535826795	,
		-0.518027009	,
		-0.500000000	,
		-0.481753674	,
		-0.463296035	,
		-0.444635179	,
		-0.425779292	,
		-0.406736643	,
		-0.387515586	,
		-0.368124553	,
		-0.348572047	,
		-0.328866647	,
		-0.309016994	,
		-0.289031797	,
		-0.268919821	,
		-0.248689887	,
		-0.228350870	,
		-0.207911691	,
		-0.187381315	,
		-0.166768747	,
		-0.146083029	,
		-0.125333234	,
		-0.104528463	,
		-0.083677843	,
		-0.062790520	,
		-0.041875654	,
		-0.020942420	,
		0
};
