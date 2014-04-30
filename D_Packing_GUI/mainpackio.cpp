#include "mainpack.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QRectF>

void Packing::readFile(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream filestream(&file);
        int num;
        filestream >> num;
        double k, x, y, w, h;
        Figure f;
        for (int i = 0; i < num; ++i)
        {
            f.clear();
            filestream >> k;
            for (int j = 0; j < k; ++j)
            {
                filestream >> x >> y >> w >> h;
                f.append(QRectF(x, y, w, h));
            }
            source.append(f);
        }
        filestream >> stripWidth;
        file.close();
    }
    fCount = source.count();
    input = source;
}

void Packing::saveGeneratedSource(QString filename, FigureList gen)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        out << gen.count() << endl;

        Figure f;
        QRectF r;
        double m = 0.0;
        double w, h;
        for (int i = 0; i < gen.count(); ++i)
        {
            f = gen[i];

            out << f.count() << endl;

            for (int j = 0; j < f.count(); ++j)
            {
                r = f[j];

                w = r.width();
                h = r.height();

                out << r.x() << " " << r.y()  << " " << w  << " " << h << endl;

                m = qMax(m, qMax(w, h));
            }
        }
        m *= 1.33;

        out << m << endl;

        file.close();
    }
}

void Packing::saveResult(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for (int i = 0; i < fCount; ++i)
        {
            out << xCoor[sourceReshuffle[i]] << " " << yCoor[sourceReshuffle[i]] << endl;
        }

        file.close();
    }
}
