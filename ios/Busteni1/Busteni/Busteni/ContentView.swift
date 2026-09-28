//
//  ContentView.swift
//  Busteni
//
//  Created by Adrian Poplesanu on 28.09.2026.
//

import SwiftUI
import AppKit

struct ContentView: View {

    @State private var cpuUsage: Double?
    @State private var memory: MemoryMetrics?

    private let green = Color.green
    private let yellow = Color.yellow
    private let red = Color.red

    var body: some View {

        VStack(alignment: .leading, spacing: 4) {

            Text("Device metrics")
                .font(.title)
                .foregroundStyle(.white)

            MetricLine(
                label: "CPU",
                value: cpuUsage.map {
                    String(format: "%.1f%%", $0)
                } ?? "--",
                valueColor: cpuColor(cpuUsage)
            )

            if let memory {

                MetricLine(
                    label: "pressure",
                    value: String(
                        format: "%.1f%%",
                        memory.pressurePercent
                    ),
                    valueColor: pressureColor(
                        memory.pressurePercent
                    )
                )

                MetricLine(
                    label: "active",
                    value: formatBytes(memory.active),
                    valueColor: usedMemoryColor(
                        memory.active,
                        total: memory.total
                    )
                )

                MetricLine(
                    label: "inactive",
                    value: formatBytes(memory.inactive),
                    valueColor: usedMemoryColor(
                        memory.inactive,
                        total: memory.total
                    )
                )

                MetricLine(
                    label: "wired",
                    value: formatBytes(memory.wired),
                    valueColor: usedMemoryColor(
                        memory.wired,
                        total: memory.total
                    )
                )

                MetricLine(
                    label: "compressed",
                    value: formatBytes(memory.compressed),
                    valueColor: usedMemoryColor(
                        memory.compressed,
                        total: memory.total
                    )
                )

                MetricLine(
                    label: "free",
                    value: formatBytes(memory.free),
                    valueColor: freeMemoryColor(
                        memory.free,
                        total: memory.total
                    )
                )

                MetricLine(
                    label: "total",
                    value: formatBytes(memory.total),
                    valueColor: .white
                )

            } else {

                Text("Unable to read memory information")
                    .foregroundStyle(.white)
            }

            Divider()
                .overlay(Color.white.opacity(0.3))
                .padding(.vertical, 4)

            Button("Quit Busteni") {
                NSApplication.shared.terminate(nil)
            }
            .buttonStyle(.plain)
            .foregroundStyle(.white.opacity(0.85))
        }
        .padding()
        .frame(minWidth: 220, alignment: .leading)
        .background(Color.black)
        .onAppear {
            updateMetrics()
        }
        .task {
            while !Task.isCancelled {

                try? await Task.sleep(for: .seconds(1))

                if Task.isCancelled {
                    break
                }

                updateMetrics()
            }
        }
    }

    private func updateMetrics() {

        cpuUsage = SystemMetrics.cpuUsage()
            .map { $0.usage }

        memory = SystemMetrics.memoryMetrics()
    }

    private func formatBytes(_ bytes: UInt64) -> String {

        let gigabytes =
            Double(bytes) / 1_073_741_824

        return String(
            format: "%.2fGB",
            gigabytes
        )
    }

    private func cpuColor(_ usage: Double?) -> Color {

        guard let usage else {
            return .white
        }

        if usage < 50 {
            return green
        }

        if usage < 80 {
            return yellow
        }

        return red
    }

    private func pressureColor(_ pressure: Double) -> Color {

        if pressure < 50 {
            return green
        }

        if pressure < 80 {
            return yellow
        }

        return red
    }

    private func usedMemoryColor(
        _ bytes: UInt64,
        total: UInt64
    ) -> Color {

        guard total > 0 else {
            return .white
        }

        let ratio = Double(bytes) / Double(total)

        if ratio < 0.30 {
            return green
        }

        if ratio < 0.60 {
            return yellow
        }

        return red
    }

    private func freeMemoryColor(
        _ bytes: UInt64,
        total: UInt64
    ) -> Color {

        guard total > 0 else {
            return .white
        }

        let ratio = Double(bytes) / Double(total)

        if ratio >= 0.20 {
            return green
        }

        if ratio >= 0.10 {
            return yellow
        }

        return red
    }
}


struct MetricLine: View {

    let label: String
    let value: String
    let valueColor: Color

    private static let labelWidth = 12

    var body: some View {

        (
            Text(paddedLabel)
                .foregroundStyle(.white)
            +
            Text(value)
                .foregroundStyle(valueColor)
        )
        .font(.body.monospaced())
        .lineLimit(1)
        .fixedSize(horizontal: true, vertical: true)
    }

    private var paddedLabel: String {

        let prefix = "\(label):"
        let padding = max(
            1,
            Self.labelWidth - prefix.count
        )

        return prefix + String(repeating: " ", count: padding)
    }
}


#Preview {
    ContentView()
}
