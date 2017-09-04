/*
 * SizeGripItem - A size grip QGraphicsItem for interactive resizing.
 *
 * Copyright (c) 2011 Cesar L. B. Silveira
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef SIZEGRIPITEM_H
#define SIZEGRIPITEM_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class SizeGripItem :public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
    private:
        enum
        {
            Top         = 0x1,
            Bottom      = 0x2,
            Left        = 0x4,
            TopLeft     = Top | Left,
            BottomLeft  = Bottom | Left,
            Right       = 0x8,
            TopRight    = Top | Right,
            BottomRight = Bottom | Right
        };

        class HandleItem : public QGraphicsRectItem
        {
            public:
                HandleItem(int positionFlags, SizeGripItem* parent);
                int positionFlags() const;

            protected:
                virtual QVariant itemChange(GraphicsItemChange change,
                                            const QVariant &value);

            private:
                QPointF restrictPosition(const QPointF& newPos);

                int positionFlags_;
                SizeGripItem* parent_;
        };

    public:
        SizeGripItem(QGraphicsItem* parent = 0);
        virtual ~SizeGripItem();
        virtual QRectF boundingRect() const;
        virtual void paint(QPainter* painter,
                           const QStyleOptionGraphicsItem* option,
                           QWidget* widget = 0);
        void setTopLeft(const QPointF& pos);
        void setTop(qreal y);
        void setTopRight(const QPointF& pos);
        void setRight(qreal x);
        void setBottomRight(const QPointF& pos);
        void setBottom(qreal y);
        void setBottomLeft(const QPointF& pos);
        void setLeft(qreal x);
	signals:
		void resizeItem(const QRectF& rect);
		qreal attached(Qt::Orientation o, qreal pos);
		//limit pos is in the ruler area
		qreal limitPos(const Qt::Edge);
    private:
		void updateHandleItemPositions();
        void doResize();

        QList<HandleItem*> handleItems_;
        QRectF rect_;
};

#endif // SIZEGRIPITEM_H
