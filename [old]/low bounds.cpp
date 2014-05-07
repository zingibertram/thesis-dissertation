DoubleList LowBounds::dff_1()
{
    return this->dff(1, 1000, 1, dff_1_func);
//    DoubleList cnt,
//            tmpowls, tmpohls,
//            tmpwls, tmphls;
//    double byk;
//    double w, h, s, ow, oh;
//    for (int i = 0; i < data.count(); ++i)
//    {
//        byk = 0;
//        for (int k = 1; k < 1000; ++k)
//        {
//            s = 0;
//            tmpowls.clear();
//            tmpohls.clear();
//            tmpwls.clear();
//            tmphls.clear();
//            for (int l = 0; l < data[i].count(); ++l)
//            {
//                for (int j = 0; j < data[i][l].count(); ++j)
//                {
//                    ow = data[i][l][j].width();
//                    oh = data[i][l][j].height();

//                    w = isw[i] ? dff_1_func(ow, k) : ow;
//                    h = ish[i] ? dff_1_func(oh, k) : oh;
//                    s += w * h;

//                    tmpowls << ow;
//                    tmpwls << w;
//                    tmpohls << oh;
//                    tmphls << h;

//                }
//            }
//            if (s > byk)
//            {
//                byk = s;

//                owls = tmpowls;
//                wls = tmpwls;
//                ohls = tmpohls;
//                hls = tmphls;
//            }
//        }
//        if (byk > dffMax)
//        {
//            dffMax = byk;
//        }
//        cnt.append(byk);//this->maximizeDff(owls, wls, ohls, hls));
//    }
//    return cnt;
}

DoubleList LowBounds::dff_2()
{
    double p = 0.0001;
    return this->dff(0, 0.5 + p - eps, p, dff_2_func);
//    DoubleList cnt,
//            tmpowls, tmpohls,
//            tmpwls, tmphls;
//    double byk;
//    double w, h, ow, oh, s;
//    for (int i = 0; i < data.count(); ++i)
//    {
//        byk = 0;
//        for (double k = 0.0; k <= 0.5; k += 0.0001)
//        {
//            s = 0;
//            tmpowls.clear();
//            tmpohls.clear();
//            tmpwls.clear();
//            tmphls.clear();
//            for (int l = 0; l < data[i].count(); ++l)
//            {
//                for (int j = 0; j < data[i][l].count(); ++j)
//                {
//                    ow = data[i][l][j].width();
//                    oh = data[i][l][j].height();

//                    w = isw[i] ? dff_2_func(ow, k) : ow;
//                    h = ish[i] ? dff_2_func(oh, k) : oh;
//                    s += w * h;
//                }
//            }
//            if (s > byk)
//            {
//                byk = s;
//            }
//        }
//        if (byk > dffMax)
//        {
//            dffMax = byk;
//        }
//        cnt.append(byk);
//    }
//    return cnt;
}

DoubleList LowBounds::dff_3()
{
    return this->dff(0, 0.5, 0.0001, dff_3_func);
//    DoubleList cnt,
//            tmpowls, tmpohls,
//            tmpwls, tmphls;
//    double byk;
//    double w, h, s, ow, oh, s;
//    for (int i = 0; i < data.count(); ++i)
//    {
//        byk = 0;
//        for (double k = 0.0; k < 0.5; k += 0.0001)
//        {
//            s = 0;
//            tmpowls.clear();
//            tmpohls.clear();
//            tmpwls.clear();
//            tmphls.clear();
//            for (int l = 0; l < data[i].count(); ++l)
//            {
//                for (int j = 0; j < data[i][l].count(); ++j)
//                {
//                    w = isw[i] ? dff_3_func(data[i][l][j].width(), k) : data[i][l][j].width();
//                    h = ish[i] ? dff_3_func(data[i][l][j].height(), k) : data[i][l][j].height();
//                    s += w * h;
//                }
//            }
//            if (s > byk)
//            {
//                byk = s;
//            }
//        }
//        if (byk > dffMax)
//        {
//            dffMax = byk;
//        }
//        cnt.append(byk);
//    }
//    return cnt;
}