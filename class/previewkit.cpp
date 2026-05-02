#include "previewkit.h"
#include <QRegularExpression>
#include <QNetworkReply>
#include <QSplitter>
#include <QGroupBox>

PreviewKit::PreviewKit(const QString &block_name, const QString &placeholder, QWidget *parent)
    : QWidget{parent} {
    // 网络管理器
    networkManager = new QNetworkAccessManager(this);


    QGroupBox *groupbox = new QGroupBox(block_name);

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(groupbox);

    QVBoxLayout *layout = new QVBoxLayout(groupbox);
    layout->setContentsMargins(15, 15, 15, 15);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    layout->addWidget(splitter);

    // 内容文本框
    contentEdit = new QPlainTextEdit();
    contentEdit->setPlaceholderText(placeholder);

    // 预览框
    previewView = new QTextBrowser();
    previewView->setAcceptRichText(true);
    previewView->setOpenExternalLinks(true);

    // 组装
    splitter->addWidget(contentEdit);
    splitter->addWidget(previewView);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);


    // 初始化计时器，单次触发
    renderTimer = new QTimer(this);
    renderTimer->setSingleShot(true);
    connect(contentEdit, &QPlainTextEdit::textChanged, [this](){
        // 文字改变，计时器 3.5s 后触发事件，否则会重新计数
        renderTimer->start(3500);
    });
    connect(renderTimer, &QTimer::timeout, this, &PreviewKit::update);
    update();
}

QString PreviewKit::getText() const {
    return contentEdit->toPlainText();
}

void PreviewKit::update() {
    QString content = contentEdit->toPlainText();
    if (content.isEmpty()) content = "... 预览区域 ...";

    // 辅助 lambda：处理公式并生成虚拟资源路径
    auto processFormula = [this, &content](const QString& regexStr, bool isBlock) {
        QRegularExpression regex(regexStr, QRegularExpression::DotMatchesEverythingOption);
        QRegularExpressionMatchIterator it = regex.globalMatch(content);

        // 我们从后往前替换，避免偏移量失效
        QList<QRegularExpressionMatch> matches;
        while (it.hasNext()) matches.prepend(it.next());

        for (const auto& match : matches) {
            QString formula = match.captured(1).trimmed();
            // 使用哈希值作为唯一的虚拟资源名
            QString resName = QString("formula_%1.svg").arg(qHash(formula));
            QUrl virtualUrl(resName);

            // 如果缓存里还没有这张图，则发起下载
            if (previewView->document()->resource(QTextDocument::ImageResource, virtualUrl).isNull()) {
                QUrl fetchUrl("http://tex.xumin.net/svg/" + QUrl::toPercentEncoding(formula));
                QNetworkReply* reply = networkManager->get(QNetworkRequest(fetchUrl));

                connect(reply, &QNetworkReply::finished, [this, reply, virtualUrl]() {
                    if (reply->error() == QNetworkReply::NoError) {
                        QByteArray data = reply->readAll();
                        // 注入内存资源
                        previewView->document()->addResource(QTextDocument::ImageResource, virtualUrl, data);
                        // 触发文档重绘
                        previewView->setHtml(previewView->toHtml());
                    }
                    reply->deleteLater();
                });
            }

            // 构造 HTML 标签
            QString imgTag;
            if (isBlock) {
                imgTag = QString("<div align='center'><img src='%1' style='height: 1.1em'></div>").arg(resName);
            } else {
                imgTag = QString("<img src='%1' style='vertical-align: middle;'>").arg(resName);
            }
            content.replace(match.capturedStart(0), match.capturedLength(0), imgTag);
        }
    };

    // 1. 处理块级公式 $$...$$
    processFormula("\\$\\$(.*?)\\$\\$", true);
    // 2. 处理行内公式 $...$
    processFormula("\\$([^\\$]+)\\$", false);

    // 3. 处理换行
    content.replace("\n", "<br>");

    QString finalHtml = QString(R"(
        <div>
            %1
        </div>
    )").arg(content);

    previewView->setHtml(finalHtml);
    // this->getText();
}
