//
//  MetricsStore.swift
//  Busteni
//
//  Created by Adrian Poplesanu on 28.09.2026.
//

import Foundation
import Observation

@MainActor
@Observable
final class MetricsStore {

    var cpuUsage: Double?
    var memory: MemoryMetrics?

    var menuBarTitle: String {

        let pressureText: String

        if let memory {
            pressureText = String(
                format: "%.0f%%",
                memory.pressurePercent
            )
        } else {
            pressureText = "--"
        }

        let cpuText: String

        if let cpuUsage {
            cpuText = String(format: "%.0f%%", cpuUsage)
        } else {
            cpuText = "--"
        }

        return "MEM: \(pressureText) | CPU: \(cpuText)"
    }

    @ObservationIgnored
    private var task: Task<Void, Never>?

    init() {
        refresh()
        start()
    }

    deinit {
        task?.cancel()
    }

    private func start() {

        task?.cancel()

        task = Task { [weak self] in

            while !Task.isCancelled {

                try? await Task.sleep(for: .seconds(10))

                if Task.isCancelled {
                    break
                }

                self?.refresh()
            }
        }
    }

    private func refresh() {

        cpuUsage = SystemMetrics.cpuUsage()
            .map { $0.usage }

        memory = SystemMetrics.memoryMetrics()
    }
}
