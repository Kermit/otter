/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2014 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#include "StatusBarWidget.h"
#include "../core/ActionsManager.h"

#include <QtWidgets/QToolButton>

namespace Otter
{

StatusBarWidget::StatusBarWidget(QWidget *parent) : QStatusBar(parent),
	m_zoomSlider(NULL)
{
}

void StatusBarWidget::setup()
{
	m_zoomSlider = new QSlider(this);
	m_zoomSlider->setRange(10, 250);
	m_zoomSlider->setTracking(true);;
	m_zoomSlider->setOrientation(Qt::Horizontal);
	m_zoomSlider->setMaximumWidth(100);

	QToolButton *zoomOutButton = new QToolButton(this);
	zoomOutButton->setDefaultAction(ActionsManager::getAction(QLatin1String("ZoomOut")));
	zoomOutButton->setAutoRaise(true);

	QToolButton *zoomInButton = new QToolButton(this);
	zoomInButton->setDefaultAction(ActionsManager::getAction(QLatin1String("ZoomIn")));
	zoomInButton->setAutoRaise(true);

	addPermanentWidget(zoomOutButton);
	addPermanentWidget(m_zoomSlider);
	addPermanentWidget(zoomInButton);
	setZoom(100);

	connect(m_zoomSlider, SIGNAL(valueChanged(int)), this, SIGNAL(requestedZoomChange(int)));
}

void StatusBarWidget::setZoom(int zoom)
{
	m_zoomSlider->setValue(zoom);
	m_zoomSlider->setToolTip(tr("Zoom %1%").arg(zoom));
}

void StatusBarWidget::setZoomEnabled(bool enabled)
{
	m_zoomSlider->setEnabled(enabled);
}

}
